#ifndef __DPL_LEXER_TOKENTYPE_H
#define __DPL_LEXER_TOKENTYPE_H

#include <iostream>

#define TOKEN_TYPES(_define)      \
    /* Literals */                \
    _define(NumberLiteral)        \
                                  \
    /* Operators */               \
    _define(AddOperator)          \
    _define(SubtractOperator)     \
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

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_TOKENTYPE_IMPL)
#define __DPL_LEXER_TOKENTYPE_IMPL

#define TOKEN_TYPE_STREAM_CASE(type) \
    case TokenType::type:            \
        os << #type;                 \
        break;

    std::ostream& operator<<(std::ostream& os, const TokenType& type)
    {
        switch (type)
        {
            TOKEN_TYPES(TOKEN_TYPE_STREAM_CASE)
        }

        return os;
    }
#endif

}

#endif