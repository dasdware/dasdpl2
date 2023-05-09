#ifndef __DPL_LEXER_LINE_H
#define __DPL_LEXER_LINE_H

#include <string>

namespace dpl::lexer
{
    typedef std::string::const_iterator SourceTextPosition;

    struct Line
    {
        size_t line;
        const std::string& source;

        SourceTextPosition begin;

        Line(size_t line, const std::string& source, SourceTextPosition begin)
            : line(line), source(source), begin(begin) {}

        SourceTextPosition end() const
        {
            for (SourceTextPosition end = begin + 1; end < source.end(); end++)
            {
                if (*end == '\n')
                {
                    return end;
                }
            }

            return source.end();
        }
    };

    std::ostream& operator<<(std::ostream& os, const Line& line);
}

#endif