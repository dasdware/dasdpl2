#ifndef __DPL_LEXER_TOKENTYPE_H
#define __DPL_LEXER_TOKENTYPE_H

#include <iostream>

#define TOKEN_TYPES(_define)      \
    /* Literals */                \
    _define(NumberLiteral)        \
                                  \
    /* Normally ignored */        \
    _define(WhiteSpace)           \
    _define(EndOfFile)            \
                                  \
    /* Lexer Errors */            \
    _define(InvalidCharacter)     \
    _define(InvalidNumberLiteral) \
    _define(InvalidToken)

#define TOKEN_TYPE_ENUM(type) type,

namespace dpl::lexer
{
    enum class TokenType
    {
        TOKEN_TYPES(TOKEN_TYPE_ENUM)
    };

    std::ostream& operator<<(std::ostream& os, const TokenType& type);
}

#endif