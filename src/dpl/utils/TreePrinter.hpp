#ifndef __DPL_UTILS_TREEPRINTER_HPP
#define __DPL_UTILS_TREEPRINTER_HPP

#include <iostream>
#include <array>

namespace dpl::utils
{
class TreePrinter {
    std::ostream& _stream;
    std::size_t _level;

    struct NodeInfo {
        int childCount;
        int childIndex;
        bool childrenPrinted;
        bool firstLine;
    };

    std::array<NodeInfo, 16> _nodeInfos;

    bool _nodePrefixWritten;
    bool _needLineBreak;

    void _writeLevelIndent(std::size_t level);
    void _writeIndent();

    void _pushLevel(int childCount);
    void _popLevel();

public:
    TreePrinter(std::ostream& stream, int childCount);

    void beginNode(int childCount);
    void beginLeaf();
    void endNode();

    template<typename T>
    void write(const T& value) {
        if (!_nodePrefixWritten) {
            _writeIndent();
            _nodePrefixWritten = true;
        }
        _stream << value;
        _needLineBreak = true;
    }

    template<typename T>
    void writeValue(const char* name, const T& value) {
        write(name);
        write(": ");
        writeLine(value);
    }

    template<typename T>
    void writeLine(const T& value) {
        if (!_nodePrefixWritten) {
            _writeIndent();
            _nodePrefixWritten = true;
        }
        _stream << value << std::endl;

        _nodePrefixWritten = false;
        _nodeInfos[_level - 1].firstLine = false;
        _needLineBreak = false;
    }

    void writeLine();
};

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_UTILS_TREEPRINTER_HPP_IMPL)
#define __DPL_UTILS_TREEPRINTER_HPP_IMPL

void TreePrinter::_writeLevelIndent(std::size_t level) {
    bool last = _nodeInfos[level - 1].childIndex >= _nodeInfos[level - 1].childCount;
    bool atLevel = level == _level - 1;

    if (atLevel) {
        if (_nodeInfos[level].firstLine) {
            if (last) {
                _stream << "+- ";
            }
            else {
                _stream << "+- ";
            }
        }
        else {
            if (last) {
                _stream << "   ";
            }
            else {
                _stream << "|  ";
            }

            if (_nodeInfos[level].childCount > 0) {
                _stream << "| ";
            }
            else {
                _stream << "  ";
            }

            _stream << ": ";
        }
    }
    else if (last) {
        _stream << "   ";
    }
    else {
        _stream << "|  ";
    }
}

void TreePrinter::_writeIndent() {
    for (std::size_t i = 1; i < _level; ++i) {
        _writeLevelIndent(i);
    }
}

void TreePrinter::_pushLevel(int childCount) {
    _nodeInfos[_level].childCount = childCount;
    _nodeInfos[_level].childIndex = 0;
    _nodeInfos[_level].childrenPrinted = false;
    _nodeInfos[_level].firstLine = true;
    _level++;
}

void TreePrinter::_popLevel() {
    _level--;
}

TreePrinter::TreePrinter(std::ostream& stream, int childCount)
    : _stream(stream),
      _level(0) {
    _pushLevel(childCount);
}

void TreePrinter::beginNode(int childCount) {
    _nodeInfos[_level - 1].childIndex++;
    _pushLevel(childCount);
    _writeIndent();

    _nodePrefixWritten = true;
    _needLineBreak = true;
}

void TreePrinter::beginLeaf() {
    beginNode(0);
}

void TreePrinter::endNode() {
    if (_needLineBreak) {
        writeLine();
    }

    _popLevel();
}

void TreePrinter::writeLine() {
    writeLine("");
}

#endif // DPL_UTILS_TREEPRINTER_HPP_IMPL
}

#endif // DPL_UTILS_TREEPRINTER_HPP