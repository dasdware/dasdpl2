#ifndef __DPL_LEXER_TOKENTYPE_H
#define __DPL_LEXER_TOKENTYPE_H

#include <iostream>

namespace dpl::lexer
{
    enum class TokenType
    {

        NumberLiteral,

        WhiteSpace,

        InvalidCharacter,
        InvalidNumberLiteral,
        EndOfFile
    };

    std::ostream &operator<<(std::ostream &os, const TokenType &type);
}

#endif