#include <dpl/parser/Parser.hpp>

int main()
{
    dpl::lexer::SourceText source("test.dpl", "789\n123  456 0a\n0b011 2\n0+a");
    dpl::lexer::Lexer lexer(source);
    dpl::parser::Parser parser(lexer);

    auto token = dpl::lexer::Token::invalid();
    do
    {
        token = parser._nextToken();

        std::cout << token << std::endl;
        token.report(std::cout);

        std::cout << std::endl;
    } while (token.type != dpl::lexer::TokenType::EndOfFile);

    return 0;
}