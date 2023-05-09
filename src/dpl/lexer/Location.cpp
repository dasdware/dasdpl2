#include <dpl/lexer/Location.h>

namespace dpl::lexer
{
    Location::Location(SourceText* sourceText, SourceTextLine line, size_t column)
        : sourceText(sourceText), line(line), column(column) {}

    std::ostream& operator<<(std::ostream& os, const Location& location)
    {
        os << location.sourceText->fileName() << ':' << (location.line->line + 1) << ':' << (location.column + 1);
        return os;
    }
}