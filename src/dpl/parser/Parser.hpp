#ifndef __DPL_PARSER_PARSER_H
#define __DPL_PARSER_PARSER_H

#include <dpl/lexer/Lexer.hpp>

namespace dpl::parser
{
    class Parser
    {
        dpl::lexer::Lexer& _lexer;

    public:
        dpl::lexer::Token _nextToken();

        Parser(dpl::lexer::Lexer& lexer);
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_PARSER_IMPL)
#define __DPL_PARSER_PARSER_IMPL

    Parser::Parser(dpl::lexer::Lexer& lexer)
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

#endif
}

#endif