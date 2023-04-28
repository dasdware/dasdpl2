#define NOBUILD_IMPLEMENTATION
#include "../vendor/nobuild/nobuild.h"

#define CPPFLAGS "-Wall", "-Wextra", "-std=c++17", "-pedantic"
#define INCLUDES "-Iinclude"

#define SRC_LEXER_LEXER PATH("src", "dpl", "lexer", "Lexer.cpp")
#define SRC_LEXER_LINE PATH("src", "dpl", "lexer", "Line.cpp")
#define SRC_LEXER_LOCATION PATH("src", "dpl", "lexer", "Location.cpp")
#define SRC_LEXER_SOURCETEXT PATH("src", "dpl", "lexer", "SourceText.cpp")
#define SRC_LEXER_TOKEN PATH("src", "dpl", "lexer", "Token.cpp")
#define SRC_LEXER_TOKENTYPE PATH("src", "dpl", "lexer", "TokenType.cpp")
#define SRC_LEXER SRC_LEXER_LEXER, SRC_LEXER_LINE, SRC_LEXER_LOCATION, SRC_LEXER_SOURCETEXT, SRC_LEXER_TOKEN, SRC_LEXER_TOKENTYPE

#define SRC_MAIN PATH("src", "main.cpp")

void build_compiler()
{
    CMD("g++.exe", INCLUDES, CPPFLAGS, "-o", "dplc.exe", SRC_LEXER, SRC_MAIN);
}

void run_compiler()
{
    CMD("dplc.exe");
}

void usage(const char *program)
{
    INFO("Usage: %s <command>", program);
    INFO("  Commands:");
    INFO("  - compile: Compiles the DasdPL compiler and creates the corresponding executable.");
    INFO("  - run    : Runs the compiler after it has been compiled.");
}

int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    const char *program = shift_args(&argc, &argv);

    if (argc == 0)
    {
        usage(program);
        PANIC("No command given.");
    }
    const char *command = shift_args(&argc, &argv);

    if (strcmp(command, "compile") == 0)
    {
        build_compiler();
    }
    else if (strcmp(command, "run") == 0)
    {
        build_compiler();
        run_compiler();
    }
    else
    {
        usage(program);
        PANIC("Unexpected command '%s'.", command);
    }

    return 0;
}
