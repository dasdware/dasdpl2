#include <dpl/parser/Parser.h>

namespace dpl::parser
{
    Parser::Parser(dpl::lexer::Lexer &lexer)
        : _lexer(lexer) {}

    dpl::lexer::Token Parser::_nextToken()
    {
        auto token = _lexer.nextToken();
        while (token.type == dpl::lexer::TokenType::WhiteSpace)
        {
            token = _lexer.nextToken();
        }

        return token;
    }
}