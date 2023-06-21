#ifndef __DPL_COMPILER_HPP
#define __DPL_COMPILER_HPP

#include <string>
#include <dpl/lexer/SourceText.hpp>
#include <dpl/lexer/Lexer.hpp>
#include <dpl/parser/Parser.hpp>
#include <dpl/parser/ast/Nodes.hpp>

namespace dpl
{

class Compiler {
    dpl::lexer::SourceText sourceText_;

public:
    Compiler(const std::string& fileName, const std::string& sourceText);

    dpl::parser::ast::node_ptr compile();
};

#if defined(DPL_IMPLEMENTATION) && !defined(__DPL_COMPILER_HPP_IMPL)
#define __DPL_COMPILER_HPP_IMPL

Compiler::Compiler(const std::string& fileName, const std::string& sourceText)
    : sourceText_(fileName, sourceText) {}

dpl::parser::ast::node_ptr Compiler::compile()
{
    sourceText_.resetLines();
    dpl::lexer::Lexer lexer(sourceText_);
    dpl::parser::Parser parser(lexer);
    return parser.parse();
}

#endif // DPL_COMPILER_HPP_IMPL
}

#endif // DPL_COMPILER_HPP