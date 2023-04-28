#ifndef __DPL_LEXER_SOURCETEXT_H
#define __DPL_LEXER_SOURCETEXT_H

#include <string>
#include <vector>

#include "Line.h"

namespace dpl::lexer
{
    typedef std::vector<Line>::const_iterator SourceTextLine;

    class SourceText
    {
        const std::string _fileName;
        const std::string _sourceText;
        std::vector<Line> _lines;

        size_t _lineNumber;

    public:
        SourceText(std::string fileName, const std::string sourceText);

        SourceTextLine newLine(std::string::const_iterator begin);

        const std::string &fileName();
        const std::string &sourceText();
    };
}

#endif