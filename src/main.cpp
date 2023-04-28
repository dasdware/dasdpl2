#include <dpl/lexer/Lexer.h>

int main()
{
    dpl::lexer::SourceText source("test.dpl", "789\n123  456 0a\n0b011 2\n0+a");
    dpl::lexer::Lexer lexer(source);

    while (true)
    {
        auto token = lexer.nextToken();

        if (token.type == dpl::lexer::TokenType::WhiteSpace)
        {
            continue;
        }

        std::cout << token << std::endl;
        token.report(std::cout);
        std::cout << std::endl;

        if (token.type == dpl::lexer::TokenType::EndOfFile)
        {
            break;
        }
    }

    return 0;
}