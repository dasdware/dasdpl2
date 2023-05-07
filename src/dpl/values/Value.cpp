#include <dpl/values/Value.h>
#include <dpl/types/NumberType.h>

namespace dpl::values
{
    Value::Value(std::any value, const dpl::types::Type &type)
        : _value(value), _type(type)
    {
    }

    Value::Value(const std::string &source, const dpl::types::Type &type)
        : _value(type.sourceToValue(source)), _type(type)
    {
    }

    const std::any &Value::value() const
    {
        return _value;
    }

    const dpl::types::Type &Value::type() const
    {
        return _type;
    }

    const std::string Value::toSource() const
    {
        return _type.valueToSource(_value);
    }

    Value Value::number(const std::string &source)
    {
        return Value(source, dpl::types::NumberType::instance());
    }

    std::ostream &
    operator<<(std::ostream &os, const Value &value)
    {
        os << "<" << value.toSource() << ": " << value.type() << ">";
        return os;
    }

}