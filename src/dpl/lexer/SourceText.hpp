#ifndef __DPL_LEXER_SOURCETEXT_H
#define __DPL_LEXER_SOURCETEXT_H

#include <string>
#include <vector>

#include <dpl/lexer/Line.hpp>

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
    SourceText(const std::string fileName, const std::string sourceText);

    SourceTextLine newLine(std::string::const_iterator begin);

    void resetLines();

    const std::string& fileName();
    const std::string& sourceText();
};

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_LEXER_SOURCETEXT_IMPL)
#define __DPL_LEXER_SOURCETEXT_IMPL

SourceText::SourceText(const std::string fileName, const std::string sourceText)
    : _fileName(fileName), _sourceText(sourceText), _lineNumber(0)
{
}

SourceTextLine SourceText::newLine(std::string::const_iterator begin)
{
    _lines.emplace_back(_lineNumber, _sourceText, begin);
    _lineNumber++;

    return (_lines.end() - 1);
}

void SourceText::resetLines()
{
    _lineNumber = 0;
    _lines.clear();
}


const std::string& SourceText::fileName()
{
    return _fileName;
}

const std::string& SourceText::sourceText()
{
    return _sourceText;
}

#endif

}

#endif