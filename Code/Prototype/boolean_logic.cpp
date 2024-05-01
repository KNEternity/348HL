#include <unordered_map>
#include <stack>
#include <cctype>
#include <stdexcept>

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
    switch (op)
    {
    case '!':
        return 3;
    case '&':
    case '@':
        return 2;
    case '|':
    case '$':
        return 1;
    default:
        return -1;
    }
}

bool isOperator(char op)
{
    return op == '&' || op == '|' || op == '!' || op == '@' || op == '$';
}

bool evaluateExpression(const std::string &expression, const std::unordered_map<char, bool> &variables)
{
    std::stack<bool> operands;
    std::stack<char> operators;

    if (expression.empty())
    {
        throw std::invalid_argument("No operands or operators present");
    }

    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];

        if (c == 'T' || c == 'F')
        {
            operands.push(c == 'T');
        }
        else if (isOperator(c))
        {
            while (!operators.empty() && getPrecedence(operators.top()) >= getPrecedence(c))
            {
                char op = operators.top();
                operators.pop();
                if (op == '!')
                {
                    if (operands.empty())
                        throw std::invalid_argument("Missing operand after 'NOT'");
                    bool operand = operands.top();
                    operands.pop();
                    operands.push(NOT(operand));
                }
                else
                {
                    if (operands.size() < 2)
                        throw std::invalid_argument("Missing operand(s) for binary operator");
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();
                    switch (op)
                    {
                    case '&':
                        operands.push(AND(operand1, operand2));
                        break;
                    case '|':
                        operands.push(OR(operand1, operand2));
                        break;
                    case '@':
                        operands.push(NAND(operand1, operand2));
                        break;
                    case '$':
                        operands.push(XOR(operand1, operand2));
                        break;
                    }
                }
            }
            operators.push(c);
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
                if (op == '!')
                {
                    if (operands.empty())
                        throw std::invalid_argument("Missing operand after 'NOT'");
                    bool operand = operands.top();
                    operands.pop();
                    operands.push(NOT(operand));
                }
                else
                {
                    if (operands.size() < 2)
                        throw std::invalid_argument("Missing operand(s) for binary operator");
                    bool operand2 = operands.top();
                    operands.pop();
                    bool operand1 = operands.top();
                    operands.pop();
                    switch (op)
                    {
                    case '&':
                        operands.push(AND(operand1, operand2));
                        break;
                    case '|':
                        operands.push(OR(operand1, operand2));
                        break;
                    case '@':
                        operands.push(NAND(operand1, operand2));
                        break;
                    case '$':
                        operands.push(XOR(operand1, operand2));
                        break;
                    }
                }
            }
            if (operators.top() != '(')
                throw std::invalid_argument("Mismatched parentheses");
            operators.pop();
        }
        else if (isalpha(c) && c != 'T' && c != 'F')
        {
            if (variables.find(c) == variables.end())
            {
                throw std::invalid_argument("Missing truth value for variable '" + std::string(1, c) + "'");
            }
            operands.push(variables.at(c));
        }
        else if (c != ' ')
        {
            throw std::invalid_argument("Unrecognized operator symbol: '" + std::string(1, c) + "'");
        }
    }
    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        if (op == '!')
        {
            if (operands.empty())
                throw std::invalid_argument("Missing operand after 'NOT'");
            bool operand = operands.top();
            operands.pop();
            operands.push(NOT(operand));
        }
        else
        {
            if (operands.size() < 2)
                throw std::invalid_argument("Missing operand(s) for binary operator");
            bool operand2 = operands.top();
            operands.pop();
            bool operand1 = operands.top();
            operands.pop();
            switch (op)
            {
            case '&':
                operands.push(AND(operand1, operand2));
                break;
            case '|':
                operands.push(OR(operand1, operand2));
                break;
            case '@':
                operands.push(NAND(operand1, operand2));
                break;
            case '$':
                operands.push(XOR(operand1, operand2));
                break;
            }
        }
    }

    if (operands.size() != 1 || !operators.empty())
    {
        throw std::invalid_argument("Invalid expression: Unresolved operands or operators");
    }

    return operands.top();
}