#ifndef __DPL_PARSER_AST_NODES_H
#define __DPL_PARSER_AST_NODES_H

#include <memory>

namespace dpl::parser::ast
{
    struct NodeVisitor;

    struct Node
    {
        virtual void accept(NodeVisitor* visitor) = 0;
    };

    typedef std::unique_ptr<Node> node_ptr;

    // COMMON NODES

    struct InvalidNode : Node {
        void accept(NodeVisitor* visitor);
    };

    node_ptr makeInvalidNode();

    // LITERAL NODES

    struct LiteralNode : public Node {
        dpl::lexer::Token literal;
    };

    struct NumberLiteralNode : public LiteralNode {
        void accept(NodeVisitor* visitor);
    };

    // BINARY OPERATOR NODES

    struct BinaryOperatorNode : Node {
        dpl::lexer::Token operation;
        node_ptr left;
        node_ptr right;
    };

    struct AddOperatorNode : BinaryOperatorNode {
        void accept(NodeVisitor* visitor);
    };

    struct SubtractOperatorNode : BinaryOperatorNode {
        void accept(NodeVisitor* visitor);
    };

    struct MultiplyOperatorNode : BinaryOperatorNode {
        void accept(NodeVisitor* visitor);
    };

    struct NodeVisitor
    {
        virtual void visitInvalidNode(InvalidNode* node) = 0;
        virtual void visitNumberLiteralNode(NumberLiteralNode* node) = 0;

        virtual void visitAddOperatorNode(AddOperatorNode* node) = 0;
        virtual void visitSubtractOperatorNode(SubtractOperatorNode* node) = 0;
        virtual void visitMultiplyOperatorNode(MultiplyOperatorNode* node) = 0;
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_AST_NODES_IMPL)
#define __DPL_PARSER_AST_NODES_IMPL

    // COMMON NODES

    void InvalidNode::accept(NodeVisitor* visitor)
    {
        visitor->visitInvalidNode(this);
    }

    node_ptr makeInvalidNode()
    {
        return std::make_unique<InvalidNode>();
    }

    // LITERAL NODES

    void NumberLiteralNode::accept(NodeVisitor* visitor)
    {
        visitor->visitNumberLiteralNode(this);
    }

    // BINARY OPERATOR NODES

    void AddOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visitAddOperatorNode(this);
    }

    void SubtractOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visitSubtractOperatorNode(this);
    }

    void MultiplyOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visitMultiplyOperatorNode(this);
    }

#endif
}

#endif