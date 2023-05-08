#include <dpl/lexer/TokenType.h>

namespace dpl::lexer
{
    std::ostream &operator<<(std::ostream &os, const TokenType &type)
    {
        switch (type)
        {
#define TOKEN_TYPE(type)  \
    case TokenType::type: \
        os << #type;      \
        break;
            TOKEN_TYPES
#undef TOKEN_TYPE
        }

        return os;
    }
}