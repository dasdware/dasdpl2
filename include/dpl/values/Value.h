#ifndef __DPL_VALUES_VALUE_H
#define __DPL_VALUES_VALUE_H

#include <any>
#include <dpl/types/Type.h>

namespace dpl::values
{
    class Value
    {
        std::any _value;
        const dpl::types::Type& _type;

    public:
        Value(std::any value, const dpl::types::Type& type);
        Value(const std::string& source, const dpl::types::Type& type);

        const std::any& value() const;
        const dpl::types::Type& type() const;

        const std::string toSource() const;

        static Value number(const std::string& source);
    };

    std::ostream& operator<<(std::ostream& os, const Value& value);
}

#endif