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

    class Parser;

    namespace parselets {
        struct PrefixParselet {
            const int precedence;

            PrefixParselet(int precedence);

            virtual ast::node_ptr parse(Parser& parser, Token token) = 0;
        };
    }

    class Parser
    {
        dpl::lexer::Lexer& _lexer;
        std::map<TokenType, std::unique_ptr<parselets::PrefixParselet>> _prefixParselets;
        std::vector<Token> _readTokens;

        Token _next();
        Token _peek(std::size_t distance);
        Token _consume();
        Token _consume(TokenType type);
        bool _match(TokenType type);

        ast::node_ptr _parse(int precedence);

    public:
        Parser(dpl::lexer::Lexer& lexer);

        ast::node_ptr parse();
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_PARSER_IMPL)
#define __DPL_PARSER_PARSER_IMPL

    namespace parselets {
        PrefixParselet::PrefixParselet(int precedence)
            : precedence(precedence)
        {
        }

        struct NumberParselet : PrefixParselet {
            NumberParselet() : PrefixParselet(0) { }

            ast::node_ptr parse(Parser&, Token token) {
                auto node = std::make_unique<ast::NumberLiteralNode>();
                node->literal = token;
                return node;
            }

        };
    }

    Parser::Parser(dpl::lexer::Lexer& lexer)
        : _lexer(lexer)
    {
        _prefixParselets[TokenType::NumberLiteral] = std::make_unique<parselets::NumberParselet>();

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

    Token Parser::_consume(TokenType type) {
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

    ast::node_ptr Parser::_parse(int precedence)
    {
        Token token = _consume();

        auto prefix = _prefixParselets.find(token.type);
        if (prefix == _prefixParselets.end()) {
            // TODO: error message
            return std::make_unique<ast::InvalidNode>();
        }

        auto left = prefix->second->parse(*this, token);
        _match(TokenType::EndOfFile);
        return left;
    }

    ast::node_ptr Parser::parse()
    {
        auto expression = _parse(0);

        return expression;
    }


#endif
}

#endif