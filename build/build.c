#define NOBUILD_IMPLEMENTATION
#include "../vendor/nobuild/nobuild.h"

#define CPPFLAGS "-Wall", "-Wextra", "-std=c++20", "-pedantic"
#define INC_DPL "-Isrc"
#define INC_CESTER "-Ivendor/libcester/include"

#define SRC_DPL PATH("src", "dpl", "dpl.cpp")

#define SRC_MAIN PATH("src", "main.cpp")
#define SRC_TEST PATH("src", "test.cpp")

void build_compiler()
{
    CMD("g++.exe", INC_DPL, CPPFLAGS, "-o", "dplc.exe", SRC_DPL, SRC_MAIN);
}

void run_compiler()
{
    CMD("dplc.exe");
}

void build_tests()
{
    CMD("g++.exe", INC_CESTER, INC_DPL, "-I.", "-Wno-write-strings", "-std=c++20",
        "-o", "tests.exe", SRC_DPL, SRC_TEST);
}

void run_tests()
{
    CMD("tests.exe");
}

void usage(const char* program)
{
    INFO("Usage: %s <command>", program);
    INFO("  Commands:");
    INFO("  - compile: Compiles the DasdPL compiler and creates the corresponding executable.");
    INFO("  - run    : Runs the compiler after it has been compiled.");
    INFO("  - test   : Build and run the tests.");
}

int main(int argc, char** argv)
{
    GO_REBUILD_URSELF(argc, argv);

    const char* program = shift_args(&argc, &argv);

    if (argc == 0)
    {
        usage(program);
        PANIC("No command given.");
    }
    const char* command = shift_args(&argc, &argv);

    if (strcmp(command, "compile") == 0)
    {
        build_compiler();
    }
    else if (strcmp(command, "run") == 0)
    {
        build_compiler();
        run_compiler();
    }
    else if (strcmp(command, "test") == 0)
    {
        build_tests();
        run_tests();
    }
    else
    {
        usage(program);
        PANIC("Unexpected command '%s'.", command);
    }

    return 0;
}
