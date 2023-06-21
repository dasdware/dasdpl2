#include <dpl/_index.hpp>

int main()
{
    dpl::Compiler compiler("test.dpl", "(123 + 456) / 789");

    auto expression = compiler.compile();

    dpl::utils::AstTreePrinter treePrinter(std::cout);
    expression->accept(&treePrinter);

    dpl::utils::AstExpressionPrinter expressionPrinter(std::cout);
    expression->accept(&expressionPrinter);
    std::cout << std::endl;

    return 0;
}