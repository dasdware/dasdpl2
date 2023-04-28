#include <iostream>
#include <string>
#include <vector>

#include "lexer/Lexer.h"

namespace dpl::tests
{
    enum class TestRunStatus
    {
        Running,
        Failed,
        Aborted
    };

    class TestRun
    {
        std::string _name;
        std::vector<std::string> _errors;
        TestRunStatus _status;

    public:
        TestRun(const std::string &name) : _name(name), _status(TestRunStatus::Running) {}

        const std::string &name()
        {
            return _name;
        }

        const std::vector<std::string> &errors()
        {
            return _errors;
        }

        void assert(bool condition, const char *error, bool critical = false)
        {
            if (!condition)
            {
                _errors.push_back(error);
                if (critical)
                {
                    _status = TestRunStatus::Aborted;
                }
                else
                {
                    _status = TestRunStatus::Failed;
                }
            }
        }
    };
}

int main()
{
    using namespace dpl::tests;
    using namespace dpl::lexer;

    TestRun lexerTestRun("LexerTokenization");

    SourceText source("test", "123");
    Lexer lexer(source);

    auto token = lexer.nextToken();
    lexerTestRun.assert(token.type == TokenType::NumberLiteral,
                        "Expected NumberLiteral");

    cout << lexerTestRun.name() << endl;
}