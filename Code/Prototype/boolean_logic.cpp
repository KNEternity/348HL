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
            if (operators.empty())
            {
                throw std::invalid_argument("Mismatched parentheses: Missing opening parenthesis");
            }
            while (operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                if (operands.size() < 1)
                {
                    throw std::invalid_argument("Missing operand after '" + std::string(1, op) + "'");
                }
                if (op != '!')
                {
                    bool operand2 = operands.top();
                    operands.pop();
                    if (operands.empty())
                    {
                        throw std::invalid_argument("Missing operand after '" + std::string(1, op) + "'");
                    }
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
                    operands.push(NOT(operands.top()));
                }
            }
            operators.pop(); // Remove the '('
        }
        else if (c == '&' || c == '|' || c == '@' || c == '$' || c == '!')
        {
            if (!operands.empty() && (operators.empty() || operators.top() == '(' || getPrecedence(operators.top()) < getPrecedence(c)))
            {
                operators.push(c);
            }
            else
            {
                throw std::invalid_argument("Invalid expression: Unexpected operator '" + std::string(1, c) + "'");
            }
        }
        else if (isalpha(c))
        {
            if (variables.find(c) == variables.end())
            {
                throw std::invalid_argument("Missing truth value for variable '" + std::string(1, c) + "'");
            }
            operands.push(variables.at(c));
        }
        else if (c != ' ') // Ignore whitespace characters
        {
            throw std::invalid_argument("Invalid character: '" + std::string(1, c) + "'");
        }
    }

    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        if (operands.size() < 1)
        {
            throw std::invalid_argument("Missing operand after '" + std::string(1, op) + "'");
        }
        if (op != '!')
        {
            bool operand2 = operands.top();
            operands.pop();
            if (operands.empty())
            {
                throw std::invalid_argument("Missing operand after '" + std::string(1, op) + "'");
            }
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
            operands.push(NOT(operands.top()));
            operands.pop();
        }
    }

    if (operands.size() != 1)
    {
        throw std::invalid_argument("Invalid expression: Unresolved operands or operators");
    }

    return operands.top();
}
