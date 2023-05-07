#ifndef __DPL_PARSER_PARSER_H
#define __DPL_PARSER_PARSER_H

#include <dpl/lexer/Lexer.h>

namespace dpl::parser
{
    class Parser
    {
        dpl::lexer::Lexer &_lexer;

    public:
        dpl::lexer::Token _nextToken();

        Parser(dpl::lexer::Lexer &lexer);
    };
}

#endif