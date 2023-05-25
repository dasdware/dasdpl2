#ifndef __DPL_LEXER_LEXER_H
#define __DPL_LEXER_LEXER_H

#include <dpl/lexer/Location.hpp>
#include <dpl/lexer/SourceText.hpp>
#include <dpl/lexer/Token.hpp>
#include <dpl/lexer/TokenType.hpp>

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

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_LEXER_IMPL)
#define __DPL_LEXER_LEXER_IMPL

    namespace characters
    {
        const char CHAR_EOF = '\0';

        bool isEOF(const char character)
        {
            return (character == CHAR_EOF);
        }

        bool isWhiteSpace(char character)
        {
            return (character == ' ') || (character == '\n') || (character == '\r') || (character == '\t');
        }

        bool isDecimalDigit(char character)
        {
            return isdigit(character);
        }

        bool isDot(char character)
        {
            return character == '.';
        }

        bool isBinaryDigit(char character)
        {
            return (character == '0') || (character == '1');
        }

        bool isOctalDigit(char character)
        {
            return (character >= '0') && (character <= '7');
        }

        bool isHexadecimalDigit(char character)
        {
            return isDecimalDigit(character) || ((character >= 'A') && (character <= 'F')) || ((character >= 'a') && (character <= 'f'));
        }

        bool isLetter(char character)
        {
            return isalpha(character);
        }
    }

    Location Lexer::startLocation()
    {
        return Location(&sourceText, startLine, startColumn);
    }

    void Lexer::startToken()
    {
        startPosition = position;
        startLine = line;
        startColumn = column;
    }

    Token Lexer::endToken(TokenType type)
    {
        return Token(startLocation(), type, startPosition, position);
    }

    char Lexer::peek()
    {
        if (position >= sourceText.sourceText().end())
        {
            return characters::CHAR_EOF;
        }

        return *position;
    }

    char Lexer::chop()
    {
        const char current = peek();
        if (characters::isEOF(current))
        {
            return current;
        }

        position++;

        if (current == '\n')
        {
            line = sourceText.newLine(position);
            column = 0;
        }
        else
        {
            column++;
        }

        return current;
    }

    Token Lexer::eof()
    {
        return endToken(TokenType::EndOfFile);
    }

    Token Lexer::invalidCharacter()
    {
        return endToken(TokenType::InvalidCharacter);
    }

    Token Lexer::whitespace()
    {
        while (isspace(peek()))
        {
            chop();
        }
        return endToken(TokenType::WhiteSpace);
    }

    Token Lexer::number(char first)
    {
        bool consumed = false;

        if (first == '0')
        {
            const char second = peek();
            switch (second)
            {
            case 'b':
                chop();
                while (characters::isBinaryDigit(peek()))
                {
                    chop();
                }
                consumed = true;
                break;
            case 'o':
                chop();
                while (characters::isOctalDigit(peek()))
                {
                    chop();
                }
                consumed = true;
                break;
            case 'x':
                chop();
                while (characters::isHexadecimalDigit(peek()))
                {
                    chop();
                }
                consumed = true;
                break;
            }
        }

        if (!consumed)
        {
            while (characters::isDecimalDigit(peek()))
            {
                chop();
            }
            if (characters::isDot(peek()))
            {
                chop();
                while (characters::isDecimalDigit(peek()))
                {
                    chop();
                }
            }
        }

        TokenType type = TokenType::NumberLiteral;
        while (characters::isLetter(peek()) || characters::isDecimalDigit(peek()) || characters::isDot(peek()))
        {
            type = TokenType::InvalidNumberLiteral;
            chop();
        }

        return endToken(type);
    }

    Lexer::Lexer(SourceText& sourceText)
        : sourceText(sourceText), column(0)
    {
        position = sourceText.sourceText().begin();
        line = sourceText.newLine(position);
    }

    Token Lexer::nextToken()
    {
        startToken();

        const char firstChar = chop();
        switch (firstChar)
        {
        case characters::CHAR_EOF:
            return eof();
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            return whitespace();
        case '(':
            return endToken(TokenType::OpenParenthesis);
        case ')':
            return endToken(TokenType::CloseParenthesis);
        case '+':
            return endToken(TokenType::AddOperator);
        case '-':
            return endToken(TokenType::SubtractOperator);
        case '*':
            return endToken(TokenType::MultiplyOperator);
        case '/':
            return endToken(TokenType::DivideOperator);
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return number(firstChar);

        default:
            return invalidCharacter();
        }
    }

#endif
}

#endif