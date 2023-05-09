#ifndef __DPL_LEXER_LOCATION_H
#define __DPL_LEXER_LOCATION_H

#include <iostream>
#include <string>

#include "SourceText.h"

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
}

#endif