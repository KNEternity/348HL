#include <unordered_map>
#include <stack>
#include <cctype>

bool AND(bool a, bool b)
{
    return a && b;
}

bool OR(bool a, bool b)
{
    return a || b;
}

bool NOT(bool a)
{
    return !a;
}

bool NAND(bool a, bool b)
{
    return !(a && b);
}

bool XOR(bool a, bool b)
{
    return (a || b) && !(a && b);
}

int getPrecedence(char op)
{
    if (op == '(' || op == ')')
        return 0;
    if (op == '&' || op == '@')
        return 1;
    if (op == '|' || op == '$')
        return 2;
    if (op == '!')
        return 3;
    return -1;
}

bool evaluateExpression(const std::string &expression, const std::unordered_map<char, bool> &variables)
{
    std::stack<bool> operands;
    std::stack<char> operators;

    for (char c : expression)
    {
        if (c == 'T' || c == 'F')
        {
            operands.push(c == 'T');
        }
        else if (c == '(')
        {
            operators.push(c);
        }
        else if (c == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                bool operand2 = operands.top();
                operands.pop();
                if (op != '!')
                {
                    bool operand1 = operands.top();
                    operands.pop();
                    if (op == '&')
                    {
                        operands.push(AND(operand1, operand2));
                    }
                    else if (op == '|')
                    {
                        operands.push(OR(operand1, operand2));
                    }
                    else if (op == '@')
                    {
                        operands.push(NAND(operand1, operand2));
                    }
                    else if (op == '$')
                    {
                        operands.push(XOR(operand1, operand2));
                    }
                }
                else
                {
                    operands.push(NOT(operand2));
                }
            }
            if (!operators.empty())
            {
                operators.pop(); // Remove the '('
            }
        }
        else if (c == '&' || c == '|' || c == '!' || c == '@' || c == '$')
        {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c))
            {
                char op = operators.top();
                operators.pop();
                bool operand2 = operands.top();
                operands.pop();
                if (op != '!')
                {
                    bool operand1 = operands.top();
                    operands.pop();
                    if (op == '&')
                    {
                        operands.push(AND(operand1, operand2));
                    }
                    else if (op == '|')
                    {
                        operands.push(OR(operand1, operand2));
                    }
                    else if (op == '@')
                    {
                        operands.push(NAND(operand1, operand2));
                    }
                    else if (op == '$')
                    {
                        operands.push(XOR(operand1, operand2));
                    }
                }
                else
                {
                    operands.push(NOT(operand2));
                }
            }
            operators.push(c);
        }
        else if (isalpha(c))
        {
            operands.push(variables.at(c));
        }
    }

    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        bool operand2 = operands.top();
        operands.pop();
        if (op != '!')
        {
            bool operand1 = operands.top();
            operands.pop();
            if (op == '&')
            {
                operands.push(AND(operand1, operand2));
            }
            else if (op == '|')
            {
                operands.push(OR(operand1, operand2));
            }
            else if (op == '@')
            {
                operands.push(NAND(operand1, operand2));
            }
            else if (op == '$')
            {
                operands.push(XOR(operand1, operand2));
            }
        }
        else
        {
            operands.push(NOT(operand2));
        }
    }

    return operands.top();
}