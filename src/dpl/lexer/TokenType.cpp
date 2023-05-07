#include <dpl/lexer/TokenType.h>

namespace dpl::lexer
{
    std::ostream &operator<<(std::ostream &os, const TokenType &type)
    {
        switch (type)
        {
        case TokenType::NumberLiteral:
            os << "NumberLiteral";
            break;
        case TokenType::WhiteSpace:
            os << "WhiteSpace";
            break;
        case TokenType::InvalidCharacter:
            os << "InvalidCharacter";
            break;
        case TokenType::InvalidNumberLiteral:
            os << "InvalidNumberLiteral";
            break;
        case TokenType::EndOfFile:
            os << "EndOfFile";
            break;
        case TokenType::InvalidToken:
            os << "InvalidToken";
            break;
        }

        return os;
    }
}