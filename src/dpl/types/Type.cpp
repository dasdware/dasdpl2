#include <dpl/types/Type.h>

namespace dpl::types
{
    Type::Type(const std::string& name)
        : _name(name)
    {
    }

    const std::string& Type::name() const
    {
        return _name;
    }

    std::ostream& operator<<(std::ostream& os, const Type& type)
    {
        os << type.name();
        return os;
    }
}