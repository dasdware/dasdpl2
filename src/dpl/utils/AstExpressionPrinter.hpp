#ifndef __DPL_UTILS_ASTEXPRESSIONPRINTER_HPP
#define __DPL_UTILS_ASTEXPRESSIONPRINTER_HPP

#include <dpl/parser/ast/Nodes.hpp>
#include <dpl/utils/TreePrinter.hpp>

namespace dpl::utils
{
    using namespace dpl::parser::ast;

    struct AstExpressionPrinter : NodeVisitor {
        void visit(InvalidNode* node);

        void visit(GroupingNode* node);

        void visitLiteral(const char* nodeName, LiteralNode* node);
        void visitBinaryOperator(const char* name, BinaryOperatorNode* node);
        void visit(AddOperatorNode* node);
        void visit(SubtractOperatorNode* node);
        void visit(MultiplyOperatorNode* node);
        void visit(DivideOperatorNode* node);

        AstExpressionPrinter(std::ostream& stream);
    private:
        std::ostream& _stream;
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_UTILS_ASTEXPRESSIONPRINTER_HPP_IMPL)
#define __DPL_UTILS_ASTEXPRESSIONPRINTER_HPP_IMPL

    AstExpressionPrinter::AstExpressionPrinter(std::ostream& stream)
        : _stream(stream)
    {
    }

    void AstExpressionPrinter::visit(InvalidNode*)
    {
        _stream << "(#INV#)";
    }

    void AstExpressionPrinter::visit(GroupingNode* node)
    {
        _stream << "(";
        node->expression->accept(this);
        _stream << ")";
    }

    void AstExpressionPrinter::visitLiteral(const char*, LiteralNode* node)
    {
        _stream << node->literal.text;
    }

    void AstExpressionPrinter::visitBinaryOperator(const char* name, BinaryOperatorNode* node)
    {
        _stream << "(";
        node->left->accept(this);
        _stream << " " << name << " ";
        node->right->accept(this);
        _stream << ")";
    }

    void AstExpressionPrinter::visit(AddOperatorNode* node)
    {
        visitBinaryOperator("+", node);
    }

    void AstExpressionPrinter::visit(SubtractOperatorNode* node)
    {
        visitBinaryOperator("-", node);
    }

    void AstExpressionPrinter::visit(MultiplyOperatorNode* node)
    {
        visitBinaryOperator("*", node);
    }

    void AstExpressionPrinter::visit(DivideOperatorNode* node)
    {
        visitBinaryOperator("/", node);
    }

#endif // DPL_UTILS_ASTEXPRESSIONPRINTER_HPP_IMPL
}

#endif // DPL_UTILS_ASTEXPRESSIONPRINTER_HPP