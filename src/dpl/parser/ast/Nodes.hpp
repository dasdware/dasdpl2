#ifndef __DPL_PARSER_AST_NODES_H
#define __DPL_PARSER_AST_NODES_H

#include <memory>

#include <dpl/parser/ast/NodeDefinitions.hpp>

#define DECL_BASE_NODE(name, fields)       \
   struct name##Node : Node {              \
        fields                             \
   };
#define DECL_ALIAS_NODE(name, parent)      \
    struct name##Node : parent##Node       \
    {                                      \
        void accept(NodeVisitor *visitor); \
    };
#define DECL_NODE(name, fields)            \
   struct name##Node : Node {              \
        fields                             \
        void accept(NodeVisitor *visitor); \
   };
#define DECL_FIELD(type, name) type name; 
#define DECL_CHILD(type, name) std::unique_ptr<type> name;

#define VISITOR_DECL_NODE(name, fields) \
    virtual void visit##name##Node(name##Node *node) = 0;
#define VISITOR_IGNORE(a, b)

namespace dpl::parser::ast
{
    using dpl::lexer::Token;

    NODES(DECL_NODE, DECL_BASE_NODE, DECL_ALIAS_NODE, DECL_FIELD, DECL_CHILD)


        struct NodeVisitor
    {
        NODES(VISITOR_DECL_NODE, VISITOR_IGNORE, VISITOR_DECL_NODE, VISITOR_IGNORE, VISITOR_IGNORE)
    };

    node_ptr makeInvalidNode();

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_PARSER_AST_NODES_IMPL)
#define __DPL_PARSER_AST_NODES_IMPL

    //#include <dpl/parser/ast/NodeVisitor.hpp>


#define IMPL_IGNORE(a, b)
#define IMPL_NODE(name, fields)                        \
    void name##Node::accept(NodeVisitor *visitor) \
    {                                             \
        visitor->visit##name##Node(this);         \
    }
#define IMPL_ALIAS_NODE(name, super) IMPL_NODE(name, )

    NODES(IMPL_NODE, IMPL_IGNORE, IMPL_ALIAS_NODE, IMPL_IGNORE, IMPL_IGNORE)

        node_ptr makeInvalidNode() {
        return std::make_unique<InvalidNode>();
    }


#endif
}

#endif