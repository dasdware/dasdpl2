#include <dpl/lexer/Location.h>

namespace dpl::lexer
{
    Location::Location(const std::string &fileName, SourceTextLine line, size_t column)
        : fileName(fileName), line(line), column(column) {}

    std::ostream &operator<<(std::ostream &os, const Location &location)
    {
        os << location.fileName << ':' << (location.line->line + 1) << ':' << (location.column + 1);
        return os;
    }
}