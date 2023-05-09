#include <dpl/lexer/TokenType.h>

#define TOKEN_TYPE_STREAM_CASE(type) \
    case TokenType::type:            \
        os << #type;                 \
        break;

namespace dpl::lexer
{
    std::ostream& operator<<(std::ostream& os, const TokenType& type)
    {
        switch (type)
        {
            TOKEN_TYPES(TOKEN_TYPE_STREAM_CASE)
        }

        return os;
    }
}