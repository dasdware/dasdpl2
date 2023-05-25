#include <dpl/parser/Parser.hpp>
#include <dpl/utils/AstTreePrinter.hpp>

int main()
{
    dpl::lexer::SourceText source("test.dpl", "(123 + 456 / 789)");
    dpl::lexer::Lexer lexer(source);
    dpl::parser::Parser parser(lexer);

    auto expression = parser.parse();

    dpl::utils::AstTreePrinter printer(std::cout);
    expression->accept(&printer);

    return 0;
}