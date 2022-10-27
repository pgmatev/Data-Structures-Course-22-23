#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "tokenizer.cpp"

#include <vector>
#include <utility>

TEST_CASE("Tokenizer test")
{

    SUBCASE("Basic test")
    {
        std::stringstream expr("123*(11+20)");

        std::vector<Token> v = {{Token::NUMBER, 0, 123},
                                {Token::OPERATOR, '*', 0},
                                {Token::OPEN_PAR, '(', 0},
                                {Token::NUMBER, 0, 11},
                                {Token::OPERATOR, '+', 0},
                                {Token::NUMBER, 0, 20},
                                {Token::CLOSE_PAR, ')', 0}};

        for (Token expectedToken:v)
        {
            Token in;
            expr >> in;
            CHECK(in.type == expectedToken.type);
            CHECK(in.value == expectedToken.value);
            CHECK(in.c == expectedToken.c);
        }
    }
    SUBCASE("Extended test")
    {
        std::stringstream expr("123   *(  11\n \r \t +   20\n\n\n)");

        std::vector<Token> v = {{Token::NUMBER, 0, 123},
                                {Token::OPERATOR, '*', 0},
                                {Token::OPEN_PAR, '(', 0},
                                {Token::NUMBER, 0, 11},
                                {Token::OPERATOR, '+', 0},
                                {Token::NUMBER, 0, 20},
                                {Token::CLOSE_PAR, ')', 0}};

        for (Token expectedToken:v)
        {
            Token in;
            expr >> in;
            CHECK(in.type == expectedToken.type);
            CHECK(in.value == expectedToken.value);
            CHECK(in.c == expectedToken.c);
        }
    }

}

TEST_CASE("Evaluate expression test")
{
    std::stringstream expr("((1+2)*3)");
    CHECK(evaluate(expr) == 9);

    std::vector<std::pair<std::string, int>> tests =
        {
            {"1", 1},
            {"((1+2)*3)", 9},
            {"((1-8)*1)", -7},
            {"((9+1)*(24/  2))", 120}
        };
    for (std::pair<std::string, int> test : tests)
    {
        std::stringstream s(test.first);
        CHECK(evaluate(s) == test.second);
    }
}

