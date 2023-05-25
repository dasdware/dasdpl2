#include <dpl/parser/Parser.hpp>
#include <dpl/utils/AstTreePrinter.hpp>

int main()
{
    dpl::lexer::SourceText source("test.dpl", "123 + 456 - 789");
    dpl::lexer::Lexer lexer(source);
    dpl::parser::Parser parser(lexer);

    auto expression = parser.parse();

    dpl::utils::AstTreePrinter printer(std::cout);
    expression->accept(&printer);

    /* auto token = dpl::lexer::Token::invalid();
     do
     {
         token = parser._nextToken();

         std::cout << token << std::endl;
         token.report(std::cout);

         std::cout << std::endl;
     } while (token.type != dpl::lexer::TokenType::EndOfFile);*/

    return 0;
}