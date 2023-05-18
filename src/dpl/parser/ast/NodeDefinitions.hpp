#include <dpl/lexer/Token.hpp>
#include <dpl/parser/ast/Node.hpp>

#define NODES(_node, _baseNode, _aliasNode, _field, _child)  \
    _node(Invalid, )                                         \
    _baseNode(Literal,                                       \
        _field(Token, literal))                              \
    _aliasNode(NumberLiteral, Literal)                       \
    _baseNode(BinaryOperator,                                \
        _field(Token, operation)                             \
        _child(Node, left)                                   \
        _child(Node, right)                                  \
    )                                                        \
    _aliasNode(AddOperator, BinaryOperator)
