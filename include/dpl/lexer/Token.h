#ifndef __DPL_LEXER_TOKEN_H
#define __DPL_LEXER_TOKEN_H

#include <iostream>
#include <vector>

#include "Location.h"
#include "TokenType.h"

namespace dpl::lexer
{
    struct Token
    {
        Location location;
        TokenType type;

        std::string::const_iterator textBegin;
        std::string::const_iterator textEnd;

        Token(const Location location,
              TokenType type, std::string::const_iterator textBegin, std::string::const_iterator textEnd);
        Token(const Token &token) = default;

        void report(std::ostream &os);
        std::string toString();

        static Token invalid();
    };

    std::ostream &operator<<(std::ostream &os, const Token &token);
}

#endif