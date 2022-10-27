#include "tokenizer.hh"

bool isWhite(char c)
{
    return c == ' ' ||
           c == '\r' || // also a new line symbol
           c == '\n' ||
           c == '\t';
}

void clearWhiteSpace(std::istream&in)
{
    while (isWhite(in.peek()))
    {
        in.get();
    }
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

std::istream& operator>>(std::istream &in, Token &t)
{
    clearWhiteSpace(in);
    char next = in.peek(); // looks at the next element of the stream without extracting

    if (isDigit(next))
    {
        t.type = Token::NUMBER;
        in >> t.value;
        t.c = 0;
    }
    else
    {
        switch(next)
        {
            case '+':
            case '-':
            case '*':
            case '/': 
                t.type = Token::OPERATOR;
                t.c = next;
                break;
            case '(':
                t.type = Token::OPEN_PAR;
                t.c = '(';
                break;
            case ')':
                t.type = Token::CLOSE_PAR;
                t.c = ')';
                break;
            default: throw "Unrecognized token!";
        }
        t.value = 0;
        in.get();
    }
    return in;
}


int compute(int left, char op, int right)
{
    switch (op)
    {
        case '+': return left + right;
        case '-': return left - right;
        case '/': return left / right;
        case '*': return left * right;
        default: throw ("Unknown operator");
    }
}

// <expression> ::= number | (<expression> <operator> <expression>)
int evaluate(std::istream& in)
{
    Token next;
    in >> next;

    if (next.type == Token::NUMBER) // <expression> ::= number
    {
        return next.value;
    }

    if (next.type == Token::OPEN_PAR) // <expression> ::= (<expression> <operator> <expression>)
    {
        int left = evaluate(in);
        Token op;
        in >> op; assert(op.type == Token::OPERATOR);
        int right = evaluate(in);
        in >> next; assert(next.type == Token::CLOSE_PAR);
        return compute(left, op.c, right);
    }
    return 0;
}