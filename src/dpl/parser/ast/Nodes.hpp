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

    struct GroupingNode : Node {
        dpl::lexer::Token openParenthesis;
        dpl::lexer::Token closeParenthesis;
        node_ptr expression;

        void accept(NodeVisitor* visitor);
    };

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

    struct DivideOperatorNode : BinaryOperatorNode {
        void accept(NodeVisitor* visitor);
    };

    struct NodeVisitor
    {
        virtual void visit(InvalidNode* node);

        virtual void visit(GroupingNode* node);

        virtual void visitLiteral(const char* nodeName, LiteralNode* node);
        virtual void visit(NumberLiteralNode* node);

        virtual void visitBinaryOperator(const char* nodeName, BinaryOperatorNode* node);
        virtual void visit(AddOperatorNode* node);
        virtual void visit(SubtractOperatorNode* node);
        virtual void visit(MultiplyOperatorNode* node);
        virtual void visit(DivideOperatorNode* node);
    };

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_AST_NODES_IMPL)
#define __DPL_PARSER_AST_NODES_IMPL

    // COMMON NODES

    void InvalidNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    node_ptr makeInvalidNode()
    {
        return std::make_unique<InvalidNode>();
    }

    void GroupingNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }


    // LITERAL NODES

    void NumberLiteralNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    // BINARY OPERATOR NODES

    void AddOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    void SubtractOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    void MultiplyOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    void DivideOperatorNode::accept(NodeVisitor* visitor)
    {
        visitor->visit(this);
    }

    // NodeVisitor

    void NodeVisitor::visit(InvalidNode*)
    {
        // empty default implementation
    }

    void NodeVisitor::visit(GroupingNode*)
    {
        // empty default implementation
    }

    void NodeVisitor::visitLiteral(const char*, LiteralNode*)
    {
        // empty default implementation
    }

    void NodeVisitor::visit(NumberLiteralNode* node)
    {
        visitLiteral("NumberLiteral", node);
    }

    void NodeVisitor::visitBinaryOperator(const char*, BinaryOperatorNode*)
    {
        // empty default implementation
    }

    void NodeVisitor::visit(AddOperatorNode* node)
    {
        visitBinaryOperator("AddOperatorNode", node);
    }

    void NodeVisitor::visit(SubtractOperatorNode* node)
    {
        visitBinaryOperator("SubtractOperatorNode", node);
    }

    void NodeVisitor::visit(MultiplyOperatorNode* node)
    {
        visitBinaryOperator("MultiplyOperatorNode", node);
    }

    void NodeVisitor::visit(DivideOperatorNode* node)
    {
        visitBinaryOperator("DivideOperatorNode", node);
    }

#endif
}

#endif