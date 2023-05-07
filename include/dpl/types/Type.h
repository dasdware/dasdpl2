#ifndef __DPL_TYPES_TYPE_H
#define __DPL_TYPES_TYPE_H

#include <any>
#include <iostream>
#include <string>

namespace dpl::types
{
    class Type
    {
    private:
        std::string _name;

    public:
        Type(const std::string &name);

        virtual const std::string &name() const;

        virtual const std::string valueToSource(const std::any &value) const = 0;
        virtual const std::any sourceToValue(const std::string &source) const = 0;
    };

    std::ostream &operator<<(std::ostream &os, const Type &type);
}

#endif