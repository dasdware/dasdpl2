#ifndef __DPL_LEXER_TOKEN_H
#define __DPL_LEXER_TOKEN_H

#include <iostream>
#include <string_view>
#include <vector>

#include <dpl/lexer/Location.hpp>
#include <dpl/lexer/TokenType.hpp>

namespace dpl::lexer
{
struct Token
{
    Location location;
    TokenType type;

    std::string_view text;

    Token();
    Token(const Location location, TokenType type, const std::string_view& text);
    Token(const Token& token) = default;

    void report(std::ostream& os);

    bool isInvalid();

    static Token invalid();
};

std::ostream& operator<<(std::ostream& os, const Token& token);

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_TOKEN_IMPL)
#define __DPL_LEXER_TOKEN_IMPL

Token::Token()
    : location(Token::invalid().location),
      text(Token::invalid().text)
{
}

Token::Token(const Location location, TokenType type, const std::string_view& text)
    : location(location), type(type), text(text)
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
    for (std::size_t i = 0; i < text.length(); ++i)
    {
        os << "~";
    }

    os << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    os << token.location << ": " << token.type;
    if (!token.text.empty())
    {
        os << ": '" << token.text << "'";
    }
    return os;
}

bool Token::isInvalid() {
    return type == TokenType::InvalidToken;
}

Token Token::invalid()
{
    static SourceText text("", "");
    static Location location(&text, text.newLine(text.sourceText().begin()), 0);
    static Token token(location, TokenType::InvalidToken,
                       std::string_view(text.sourceText()));
    return token;
}

#endif
}

#endif