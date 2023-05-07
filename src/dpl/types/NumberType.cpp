#include <dpl/types/NumberType.h>
#include <sstream>

namespace dpl::types
{
    NumberType::NumberType()
        : Type("Number")
    {
    }

    const std::string NumberType::valueToSource(const std::any &value) const
    {
        std::ostringstream stream;
        stream << std::any_cast<double>(value);
        return stream.str();
    }

    const std::any NumberType::sourceToValue(const std::string &source) const
    {
        return std::make_any<double>(std::stod(source));
    }

    const NumberType &NumberType::instance()
    {
        static NumberType theInstance;
        return theInstance;
    }
}