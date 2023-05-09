#ifndef __DPL_PARSER_AST_NUMBERLITERALNODE_H
#define __DPL_PARSER_AST_NUMBERLITERALNODE_H

#include <dpl/lexer/Token.h>
#include "Node.h"

namespace dpl::parser::ast
{
    class NumberLiteralNode : Node
    {
        dpl::lexer::Token _literal;

    public:
        NumberLiteralNode(const dpl::lexer::Token& literal);
    };
}

#endif