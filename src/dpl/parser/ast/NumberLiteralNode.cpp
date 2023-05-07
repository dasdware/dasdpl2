#include <dpl/parser/ast/NumberLiteralNode.h>

namespace dpl::parser::ast
{

    NumberLiteralNode::NumberLiteralNode(const dpl::lexer::Token &literal)
        : _literal(literal)
    {
    }
}