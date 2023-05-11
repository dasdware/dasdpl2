#ifndef __DPL_PARSER_AST_NODE_H
#define __DPL_PARSER_AST_NODE_H

namespace dpl::parser::ast
{
    class NodeVisitor;

    struct Node
    {
        virtual void accept(NodeVisitor* visitor) = 0;
    };
}
#endif
