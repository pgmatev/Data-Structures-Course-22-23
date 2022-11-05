#ifndef TOKENIZER_HH
#define TOKENIZER_HH

#include <iostream>
#include <cassert>


struct Token
{
    enum TokenType {OPEN_PAR, CLOSE_PAR, NUMBER, OPERATOR, EOE};

    TokenType type;
    char c;
    int value; //inheriting classes is more correct but it is overengineering
              // so in this case it is acceptable to have an extra variable for numbers
};

// void clearWhiteSpace(std::istream&in);

// bool isWhite(char c);

// bool isDigit(char c);

// std::ostream& operator>>(std::istream &in, Token &t);

#endif