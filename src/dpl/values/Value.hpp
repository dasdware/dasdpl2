#ifndef __DPL_VALUES_VALUE_H
#define __DPL_VALUES_VALUE_H

#include <any>
#include <dpl/types/Type.hpp>

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

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_VALUES_VALUE_IMPL)
#define __DPL_VALUES_VALUE_IMPL

#include <dpl/types/NumberType.hpp>

Value::Value(std::any value, const dpl::types::Type& type)
    : _value(value), _type(type)
{
}

Value::Value(const std::string& source, const dpl::types::Type& type)
    : _value(type.sourceToValue(source)), _type(type)
{
}

const std::any& Value::value() const
{
    return _value;
}

const dpl::types::Type& Value::type() const
{
    return _type;
}

const std::string Value::toSource() const
{
    return _type.valueToSource(_value);
}

Value Value::number(const std::string& source)
{
    return Value(source, dpl::types::NumberType::instance());
}

std::ostream&
operator<<(std::ostream& os, const Value& value)
{
    os << "<" << value.toSource() << ": " << value.type() << ">";
    return os;
}

#endif
}

#endif