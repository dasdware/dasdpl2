#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <exotic/cester.h>

#include <dpl/lexer/Lexer.h>

CESTER_BEFORE_ALL(instance,
                  CESTER_VERBOSE_LEVEL(2);)

#define assert_token_type(expected, actual)                                                                                    \
    do                                                                                                                         \
    {                                                                                                                          \
        if (expected != actual)                                                                                                \
        {                                                                                                                      \
            std::stringstream expectedStream;                                                                                  \
            expectedStream << expected;                                                                                        \
            std::stringstream actualStream;                                                                                    \
            actualStream << actual;                                                                                            \
            cester_evaluate_expect_actual(0, 1, expectedStream.str().c_str(), actualStream.str().c_str(), __FILE__, __LINE__); \
        }                                                                                                                      \
    } while (false)

#define assert_token(lexer, token_type, token_value)                      \
    do                                                                    \
    {                                                                     \
        auto __token = lexer.nextToken();                                 \
        assert_token_type(token_type, __token.type);                      \
        cester_assert_str_equal(token_value, __token.toString().c_str()); \
    } while (false)

#define LEXER_LITERAL_TEST(name, token_type, token_value)          \
    CESTER_TEST(name, instance,                                    \
                dpl::lexer::SourceText source(#name, token_value); \
                dpl::lexer::Lexer lexer(source);                   \
                assert_token(lexer, token_type, token_value);)

LEXER_LITERAL_TEST(Lexer_NumberLiteral_Integer, dpl::lexer::TokenType::NumberLiteral, "1234")
LEXER_LITERAL_TEST(Lexer_NumberLiteral_Decimal, dpl::lexer::TokenType::NumberLiteral, "123.456")
LEXER_LITERAL_TEST(Lexer_NumberLiteral_Binary, dpl::lexer::TokenType::NumberLiteral, "0b0101")
LEXER_LITERAL_TEST(Lexer_NumberLiteral_Octal, dpl::lexer::TokenType::NumberLiteral, "0o7654")
LEXER_LITERAL_TEST(Lexer_NumberLiteral_Hexadecimal, dpl::lexer::TokenType::NumberLiteral, "0xcAfE9876")

LEXER_LITERAL_TEST(Lexer_InvalidNumberLiteral_BadDigit, dpl::lexer::TokenType::InvalidNumberLiteral, "1234a")
LEXER_LITERAL_TEST(Lexer_InvalidNumberLiteral_MultipleDots, dpl::lexer::TokenType::InvalidNumberLiteral, "123.456.789")

LEXER_LITERAL_TEST(Lexer_WhiteSpace_Space, dpl::lexer::TokenType::WhiteSpace, " ")
LEXER_LITERAL_TEST(Lexer_WhiteSpace_Tab, dpl::lexer::TokenType::WhiteSpace, "\t")
LEXER_LITERAL_TEST(Lexer_WhiteSpace_CarriageReturn, dpl::lexer::TokenType::WhiteSpace, "\r")
LEXER_LITERAL_TEST(Lexer_WhiteSpace_NewLine, dpl::lexer::TokenType::WhiteSpace, "\n")
LEXER_LITERAL_TEST(Lexer_WhiteSpace_All, dpl::lexer::TokenType::WhiteSpace, " \t\r\n")