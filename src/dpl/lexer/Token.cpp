#include <dpl/lexer/Token.h>

namespace dpl::lexer
{
    Token::Token(const Location location,
                 TokenType type, std::string::const_iterator textBegin, std::string::const_iterator textEnd)
        : location(location),
          type(type), textBegin(textBegin), textEnd(textEnd)
    {
    }

    void Token::report(std::ostream &os)
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

    std::ostream &operator<<(std::ostream &os, const Token &token)
    {
        os << token.location << ": " << token.type;
        if (token.textEnd > token.textBegin)
        {
            os << ": '" << std::string(token.textBegin, token.textEnd) << "'";
        }
        return os;
    }
}