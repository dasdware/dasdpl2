#ifndef __DPL_LEXER_LEXER_H
#define __DPL_LEXER_LEXER_H

#include "Location.h"
#include "SourceText.h"
#include "Token.h"
#include "TokenType.h"

namespace dpl::lexer
{
    class Lexer
    {
        SourceText& sourceText;

        std::string::const_iterator position;
        SourceTextLine line;
        size_t column;

        std::string::const_iterator startPosition;
        SourceTextLine startLine;
        size_t startColumn;

        Location startLocation();

        void startToken();
        Token endToken(TokenType type);

        char peek();
        char chop();

        Token eof();
        Token invalidCharacter();
        Token whitespace();
        Token number(char first);

    public:
        Lexer(SourceText& sourceText);

        Token nextToken();
    };
}

#endif