#include <dpl/lexer/SourceText.h>

namespace dpl::lexer
{
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

    const std::string &SourceText::fileName()
    {
        return _fileName;
    }

    const std::string &SourceText::sourceText()
    {
        return _sourceText;
    }
}
