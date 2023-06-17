#ifndef __DPL_LEXER_LOCATION_H
#define __DPL_LEXER_LOCATION_H

#include <iostream>
#include <string>

#include <dpl/lexer/SourceText.hpp>

namespace dpl::lexer
{

struct Location
{
    SourceText* sourceText;
    SourceTextLine line;
    size_t column;

    Location(SourceText* sourceText, SourceTextLine line, size_t column);
};

std::ostream& operator<<(std::ostream& os, const Location& location);

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_LOCATION_IMPL)
#define __DPL_LEXER_LOCATION_IMPL

Location::Location(SourceText* sourceText, SourceTextLine line, size_t column)
    : sourceText(sourceText), line(line), column(column) {}

std::ostream& operator<<(std::ostream& os, const Location& location)
{
    os << location.sourceText->fileName() << ':' << (location.line->line + 1) << ':' << (location.column + 1);
    return os;
}

#endif
}

#endif