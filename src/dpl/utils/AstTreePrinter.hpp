#ifndef __DPL_UTILS_ASTTREEPRINTER_HPP
#define __DPL_UTILS_ASTTREEPRINTER_HPP

#include <dpl/parser/ast/Nodes.hpp>
#include <dpl/utils/TreePrinter.hpp>

namespace dpl::utils
{
using namespace dpl::parser::ast;

struct AstTreePrinter : NodeVisitor {
    void visit(InvalidNode* node);

    void visit(GroupingNode* node);

    void visitLiteral(const char* nodeName, LiteralNode* node);
    void visitBinaryOperator(const char* name, BinaryOperatorNode* node);

    AstTreePrinter(std::ostream& stream);
private:
    TreePrinter _printer;

    void _writeTokenLine(const char* label, dpl::lexer::Token token);
};

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_UTILS_ASTTREEPRINTER_HPP_IMPL)
#define __DPL_UTILS_ASTTREEPRINTER_HPP_IMPL

AstTreePrinter::AstTreePrinter(std::ostream& stream)
    : _printer(stream, 1)
{
}

void AstTreePrinter::_writeTokenLine(const char* label, dpl::lexer::Token token)
{
    _printer.write(label);
    _printer.write(": '");
    _printer.write(token.text);
    _printer.write("' @ ");
    _printer.writeLine(token.location);
}

void AstTreePrinter::visit(InvalidNode*)
{
    _printer.beginLeaf();
    {
        _printer.writeLine("Invalid");
    }
    _printer.endNode();
}

void AstTreePrinter::visit(GroupingNode* node)
{
    _printer.beginNode(1);
    {
        _printer.writeLine("Grouping");
        _writeTokenLine("OpenParenthesis", node->openParenthesis);
        _writeTokenLine("CloseParenthesis", node->closeParenthesis);
        node->expression->accept(this);
    }
    _printer.endNode();
}

void AstTreePrinter::visitLiteral(const char* nodeName, LiteralNode* node)
{
    _printer.beginLeaf();
    {
        _printer.writeLine(nodeName);
        _writeTokenLine("Value", node->literal);
    }
    _printer.endNode();
}

void AstTreePrinter::visitBinaryOperator(const char* name, BinaryOperatorNode* node)
{
    _printer.beginNode(2);
    {
        _printer.writeLine(name);
        _writeTokenLine("Operation", node->operation);
        node->left->accept(this);
        node->right->accept(this);
    }
    _printer.endNode();
}

#endif // DPL_UTILS_ASTPRINTER_HPP_IMPL
}

#endif // DPL_UTILS_ASTPRINTER_HPP