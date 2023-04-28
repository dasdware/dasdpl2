#include <iostream>
#include <iomanip>

#include <dpl/lexer/Line.h>

namespace dpl::lexer
{
    std::ostream &operator<<(std::ostream &os, const Line &line)
    {
        os << std::setw(4) << std::setfill(' ') << (line.line + 1) << " | " << std::string(line.begin, line.end());
        return os;
    }
}