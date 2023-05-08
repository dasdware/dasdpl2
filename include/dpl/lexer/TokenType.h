#ifndef __DPL_LEXER_TOKENTYPE_H
#define __DPL_LEXER_TOKENTYPE_H

#include <iostream>

#define TOKEN_TYPES                  \
    /* Literals */                   \
    TOKEN_TYPE(NumberLiteral)        \
                                     \
    /* Normally ignored */           \
    TOKEN_TYPE(WhiteSpace)           \
    TOKEN_TYPE(EndOfFile)            \
                                     \
    /* Lexer Errors */               \
    TOKEN_TYPE(InvalidCharacter)     \
    TOKEN_TYPE(InvalidNumberLiteral) \
    TOKEN_TYPE(InvalidToken)

namespace dpl::lexer
{
    enum class TokenType
    {
#define TOKEN_TYPE(type) type,
        TOKEN_TYPES
#undef TOKEN_TYPE
    };

    std::ostream &operator<<(std::ostream &os, const TokenType &type);
}

#endif