#ifndef __DPL_PARSER_AST_NODE_H
#define __DPL_PARSER_AST_NODE_H

#include <memory>

namespace dpl::parser::ast
{
    class NodeVisitor;

    struct Node
    {
        virtual void accept(NodeVisitor* visitor) = 0;
    };

    typedef std::unique_ptr<Node> node_ptr;
}
#endif
