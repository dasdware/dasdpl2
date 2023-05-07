#ifndef __DPL_TYPES_NUMBERTYPE_H
#define __DPL_TYPES_NUMBERTYPE_H

#include <string>
#include "Type.h"

namespace dpl::types
{
    class NumberType : public Type
    {
    public:
        static const NumberType &instance();

    private:
        NumberType();

    public:
        NumberType(NumberType const &) = delete;
        void operator=(NumberType const &) = delete;

        const std::string valueToSource(const std::any &value) const;
        const std::any sourceToValue(const std::string &source) const;
    };
}

#endif