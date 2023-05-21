#ifndef __DPL_UTILS_ASTPRINTER_HPP
#define __DPL_UTILS_ASTPRINTER_HPP

#include <dpl/parser/ast/Nodes.hpp>
#include <dpl/utils/TreePrinter.hpp>

namespace dpl::utils
{
    using namespace dpl::parser::ast;

    struct AstPrinter : NodeVisitor {
        void visitInvalidNode(InvalidNode* node);
        void visitNumberLiteralNode(NumberLiteralNode* node);
        void visitAddOperatorNode(AddOperatorNode* node);

        AstPrinter(std::ostream& stream);
    private:
        TreePrinter _printer;
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_UTILS_ASTPRINTER_HPP_IMPL)
#define __DPL_UTILS_ASTPRINTER_HPP_IMPL

    AstPrinter::AstPrinter(std::ostream& stream)
        : _printer(stream, 1)
    {
    }


    void AstPrinter::visitInvalidNode(InvalidNode*)
    {
        _printer.beginLeaf();
        {
            _printer.writeLine("Invalid");
        }
        _printer.endNode();

    }

    void AstPrinter::visitNumberLiteralNode(NumberLiteralNode* node)
    {
        _printer.beginLeaf();
        {
            _printer.writeLine("NumberLiteral");
            _printer.writeValue("Location", node->literal.location);
            _printer.writeValue("Value", node->literal.toString());
        }
        _printer.endNode();
    }

    void AstPrinter::visitAddOperatorNode(AddOperatorNode* node)
    {
        _printer.beginNode(2);
        {
            _printer.writeLine("AddOperator");
            _printer.writeValue("Location", node->operation.location);
            node->left->accept(this);
            node->right->accept(this);
        }
        _printer.endNode();
    }

#endif // DPL_UTILS_ASTPRINTER_HPP_IMPL
}

#endif // DPL_UTILS_ASTPRINTER_HPP