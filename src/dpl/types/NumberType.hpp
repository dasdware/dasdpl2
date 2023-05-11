#ifndef __DPL_TYPES_NUMBERTYPE_H
#define __DPL_TYPES_NUMBERTYPE_H

#include <string>
#include <dpl/types/Type.hpp>

namespace dpl::types
{
    class NumberType : public Type
    {
    public:
        static const NumberType& instance();

    private:
        NumberType();

    public:
        NumberType(NumberType const&) = delete;
        void operator=(NumberType const&) = delete;

        const std::string valueToSource(const std::any& value) const;
        const std::any sourceToValue(const std::string& source) const;
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_TYPES_NUMBERTYPE_IMPL)
#define __DPL_TYPES_NUMBERTYPE_IMPL

    NumberType::NumberType()
        : Type("Number")
    {
    }

    const std::string NumberType::valueToSource(const std::any& value) const
    {
        std::ostringstream stream;
        stream << std::any_cast<double>(value);
        return stream.str();
    }

    const std::any NumberType::sourceToValue(const std::string& source) const
    {
        return std::make_any<double>(std::stod(source));
    }

    const NumberType& NumberType::instance()
    {
        static NumberType theInstance;
        return theInstance;
    }

#endif
}

#endif