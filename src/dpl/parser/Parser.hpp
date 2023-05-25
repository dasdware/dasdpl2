#ifndef __DPL_PARSER_PARSER_H
#define __DPL_PARSER_PARSER_H

#include <map>
#include <memory>
#include <vector>

#include <dpl/lexer/Lexer.hpp>
#include <dpl/parser/ast/Nodes.hpp>

namespace dpl::parser
{
    using dpl::lexer::Token;
    using dpl::lexer::TokenType;

    enum class Precedence
    {
        None = 0,
        Assignment,
        Conditional,
        Sum,
        Product,
        Exponent,
        Prefix,
        Postfix,
        Call,
    };

    class Parser;

    namespace parselets {
        struct PrefixParselet {
            const Precedence precedence;

            PrefixParselet(Precedence precedence);

            virtual ast::node_ptr parse(Parser& parser, Token token) = 0;
        };

        struct InfixParselet {
            const Precedence precedence;

            InfixParselet(Precedence precedence);

            virtual ast::node_ptr parse(Parser& parser, ast::node_ptr left, Token token) = 0;
        };
    }

    class Parser
    {
        dpl::lexer::Lexer& _lexer;
        std::map<TokenType, std::unique_ptr<parselets::PrefixParselet>> _prefixParselets;
        std::map<TokenType, std::unique_ptr<parselets::InfixParselet>> _infixParselets;
        std::vector<Token> _readTokens;

        Token _next();
        Token _peek(std::size_t distance);
        Token _consume();
        bool _match(TokenType type);
        Precedence _getPrecedence();

    public:
        Parser(dpl::lexer::Lexer& lexer);

        ast::node_ptr parse();
        ast::node_ptr parse(Precedence precedence);

        Token consume(TokenType type);
        Token expect(TokenType type);

    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_PARSER_IMPL)
#define __DPL_PARSER_PARSER_IMPL

    namespace parselets {
        PrefixParselet::PrefixParselet(Precedence precedence)
            : precedence(precedence)
        {
        }

        struct GroupingParselet : PrefixParselet {
            GroupingParselet() : PrefixParselet(Precedence::None) {}

            ast::node_ptr parse(Parser& parser, Token token) {
                auto node = std::make_unique<ast::GroupingNode>();
                node->openParenthesis = token;
                node->expression = parser.parse(precedence);
                node->closeParenthesis = parser.expect(TokenType::CloseParenthesis);
                return node;
            }
        };

        template <class T>
        struct LiteralParselet : PrefixParselet {
            LiteralParselet(Precedence precedence) : PrefixParselet(precedence) {}

            ast::node_ptr parse(Parser&, Token token) {
                auto node = std::make_unique<T>();
                node->literal = token;
                return node;
            }
        };

        InfixParselet::InfixParselet(Precedence precedence)
            : precedence(precedence)
        {
        }

        template <class T>
        struct BinaryOperatorParselet : InfixParselet {
            const bool isRight;

            BinaryOperatorParselet(Precedence precedence, bool isRight)
                : InfixParselet(precedence), isRight(isRight) {}

            ast::node_ptr parse(Parser& parser, ast::node_ptr left, Token token) {
                ast::node_ptr right = parser.parse(
                    static_cast<Precedence>(static_cast<int>(precedence) - (isRight ? 1 : 0)));

                auto node = std::make_unique<T>();
                node->operation = token;
                node->left = std::move(left);
                node->right = std::move(right);
                return node;
            }
        };
    }

    Parser::Parser(dpl::lexer::Lexer& lexer)
        : _lexer(lexer)
    {
        _prefixParselets[TokenType::NumberLiteral] = std::make_unique<
            parselets::LiteralParselet<ast::NumberLiteralNode>>(Precedence::None);
        _prefixParselets[TokenType::OpenParenthesis] = std::make_unique<
            parselets::GroupingParselet>();

        _infixParselets[TokenType::AddOperator] = std::make_unique<
            parselets::BinaryOperatorParselet<ast::AddOperatorNode>>(Precedence::Sum, false);
        _infixParselets[TokenType::SubtractOperator] = std::make_unique<
            parselets::BinaryOperatorParselet<ast::SubtractOperatorNode>>(Precedence::Sum, false);
        _infixParselets[TokenType::MultiplyOperator] = std::make_unique<
            parselets::BinaryOperatorParselet<ast::MultiplyOperatorNode>>(Precedence::Product, false);
        _infixParselets[TokenType::DivideOperator] = std::make_unique<
            parselets::BinaryOperatorParselet<ast::DivideOperatorNode>>(Precedence::Product, false);
    }

    Token Parser::_next()
    {
        auto token = _lexer.nextToken();
        while (token.type == dpl::lexer::TokenType::WhiteSpace)
        {
            token = _lexer.nextToken();
        }

        return token;
    }

    Token Parser::_peek(std::size_t distance)
    {
        while (distance >= _readTokens.size()) {
            _readTokens.push_back(_next());
        }

        return _readTokens[distance];
    }

    Token Parser::_consume()
    {
        _peek(0);

        auto token = _readTokens[0];
        _readTokens.erase(_readTokens.begin());

        return token;
    }

    Token Parser::consume(TokenType type) {
        auto token = _peek(0);
        if (token.type != type) {
            // TODO: Error message
            return Token::invalid();
        }

        return _consume();
    }

    bool Parser::_match(TokenType type) {
        auto token = _peek(0);
        if (token.type != type) {
            // TODO: Error message
            std::cerr << token.location << ": ERROR: Unexpected " << token.type << ", expected " << type << std::endl;
            token.report(std::cerr);
            return false;
        }

        _consume();
        return true;
    }

    Token Parser::expect(TokenType type)
    {
        auto token = _peek(0);
        if (token.type != type) {
            // TODO: Error message
            std::cerr << token.location << ": ERROR: Unexpected " << token.type << ", expected " << type << std::endl;
            token.report(std::cerr);
            return Token::invalid();
        }

        _consume();
        return token;
    }


    Precedence Parser::_getPrecedence() {
        auto parser = _infixParselets.find(_peek(0).type);
        if (parser == _infixParselets.end()) {
            return Precedence::None;
        }

        return parser->second->precedence;
    }

    ast::node_ptr Parser::parse(Precedence precedence)
    {
        Token token = _consume();

        auto prefix = _prefixParselets.find(token.type);
        if (prefix == _prefixParselets.end()) {
            // TODO: error message
            return std::make_unique<ast::InvalidNode>();
        }

        auto left = prefix->second->parse(*this, token);

        while (precedence < _getPrecedence()) {
            token = _consume();

            auto infix = _infixParselets.find(token.type);
            left = infix->second->parse(*this, std::move(left), token);
        }

        return left;
    }

    ast::node_ptr Parser::parse()
    {
        auto expression = parse(Precedence::None);
        _match(TokenType::EndOfFile);
        return expression;
    }

#endif
}

#endif