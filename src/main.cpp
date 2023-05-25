#include <dpl/parser/Parser.hpp>
#include <dpl/utils/AstTreePrinter.hpp>
#include <dpl/utils/AstExpressionPrinter.hpp>

int main()
{
    dpl::lexer::SourceText source("test.dpl", "(123 + 456) / 789");
    dpl::lexer::Lexer lexer(source);
    dpl::parser::Parser parser(lexer);

    auto expression = parser.parse();

    dpl::utils::AstTreePrinter treePrinter(std::cout);
    expression->accept(&treePrinter);

    dpl::utils::AstExpressionPrinter expressionPrinter(std::cout);
    expression->accept(&expressionPrinter);
    std::cout << std::endl;

    return 0;
}