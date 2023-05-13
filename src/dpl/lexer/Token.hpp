#ifndef __DPL_LEXER_TOKEN_H
#define __DPL_LEXER_TOKEN_H

#include <iostream>
#include <vector>

#include <dpl/lexer/Location.hpp>
#include <dpl/lexer/TokenType.hpp>

namespace dpl::lexer
{
    struct Token
    {
        Location location;
        TokenType type;

        std::string::const_iterator textBegin;
        std::string::const_iterator textEnd;

        Token();
        Token(const Location location,
            TokenType type, std::string::const_iterator textBegin, std::string::const_iterator textEnd);
        Token(const Token& token) = default;

        void report(std::ostream& os);
        std::string toString();

        static Token invalid();
    };

    std::ostream& operator<<(std::ostream& os, const Token& token);

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_TOKEN_IMPL)
#define __DPL_LEXER_TOKEN_IMPL

    Token::Token()
        : location(Token::invalid().location),
        textBegin(Token::invalid().textBegin),
        textEnd(Token::invalid().textEnd)
    {
    }

    Token::Token(const Location location,
        TokenType type, std::string::const_iterator textBegin, std::string::const_iterator textEnd)
        : location(location),
        type(type), textBegin(textBegin), textEnd(textEnd)
    {
    }

    void Token::report(std::ostream& os)
    {
        os << *(location.line) << std::endl;
        os << "     | ";
        for (size_t i = 0; i < location.column; ++i)
        {
            os << " ";
        }

        os << "^";
        for (int i = 0; i < textEnd - textBegin - 1; ++i)
        {
            os << "~";
        }

        os << std::endl;
    }

    std::string Token::toString()
    {
        return std::string(textBegin, textEnd);
    }

    std::ostream& operator<<(std::ostream& os, const Token& token)
    {
        os << token.location << ": " << token.type;
        if (token.textEnd > token.textBegin)
        {
            os << ": '" << std::string(token.textBegin, token.textEnd) << "'";
        }
        return os;
    }

    Token Token::invalid()
    {
        static SourceText text("", "");
        static Location location(&text, text.newLine(text.sourceText().begin()), 0);
        static Token token(location, TokenType::InvalidToken, text.sourceText().begin(), text.sourceText().end());
        return token;
    }

#endif
}

#endif