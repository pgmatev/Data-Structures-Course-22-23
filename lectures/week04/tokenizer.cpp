#include "tokenizer.hh"

#include <stack>

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

bool hasPriority(char op)
{
    return op == '*' || op == '/';
}

bool isParenthesis(char c)
{
    return c == '(' || c == ')';
}

std::istream& operator>>(std::istream &in, Token &t)
{
    clearWhiteSpace(in);
    char next = in.peek(); // looks at the next element of the stream without extracting

    if(!in || in.eof())
    {
        return in;
    }

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
                break;
            case '(':
                t.type = Token::OPEN_PAR;
                break;
            case ')':
                t.type = Token::CLOSE_PAR;
                break;
            case '!':
                t.type = Token::EOE;
                break;
            default: throw "Unrecognized token!";
        }
        t.c = next;
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

int evaluateRPN(std::istream& in)
{
    std::stack<int> s;

    Token t;
    in >> t;
    while (in)
    {
        if ( t.type == Token::NUMBER)
        {
            s.push(t.value);
        }
        else
        {
            assert(t.type == Token::OPERATOR);
            assert(s.size() >= 2);
            int right = s.top();
            s.pop();
            int left = s.top();
            s.pop();
            s.push(compute(left, t.c, right));
        }
        in >> t;
    }
    assert(s.size() == 1);
    return s.top();
}

std::stringstream InfixToRPN(std::istream& in)
{
    std::stringstream output;
    std::stack<char> operatorStack;
    Token t;
    in >> t;

    while (in)
    {
        switch(t.type)
        {
            case Token::NUMBER:
                output << t.value << " ";
                break;
            case Token::OPERATOR:
                if (!hasPriority(t.c))
                {
                    while (operatorStack.size() > 0 && !isParenthesis(operatorStack.top()))
                    {
                        output << operatorStack.top() << " ";
                        operatorStack.pop();
                    }     
                    operatorStack.push(t.c);
                }
                else
                {
                    operatorStack.push(t.c);
                }
                break;
            case Token::CLOSE_PAR:
                while (operatorStack.size() > 0 && !isParenthesis(operatorStack.top()))
                {
                    output << operatorStack.top() << " ";
                    operatorStack.pop();
                }
                assert(operatorStack.size() > 0);
                operatorStack.pop();
                break;
            default: assert(false);
        }
        in >> t;
    }
    while (operatorStack.size() != 0)
    {
        output << operatorStack.top() << " ";
        operatorStack.pop();
    }
    return output;
}