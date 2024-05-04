#include "boolean_logic.h"
#include <unordered_map>
#include <stack>
#include <cctype>
#include <stdexcept>

/*
    This code block contains functions for boolean logic operations, operator precedence determination, and expression evaluation.
    It handles logical operations like AND, OR, NOT, NAND, XOR, and evaluates expressions with variables and parentheses.

    Key Functions:
    - bool AND(bool a, bool b): Performs logical AND operation on two boolean values.
    - bool OR(bool a, bool b): Performs logical OR operation on two boolean values.
    - bool NOT(bool a): Performs logical NOT operation on a boolean value.
    - bool NAND(bool a, bool b): Performs NAND operation on two boolean values.
    - bool XOR(bool a, bool b): Performs XOR operation on two boolean values.
    - int getPrecedence(char op): Returns the precedence level of operators for expression evaluation.
    - bool isOperator(char op): Checks if a character is a logical operator.
    - bool evaluateExpression(const std::string &expression, const std::unordered_map<char, bool> &variables): Evaluates a boolean expression with variables.

    Error Handling:
    - Checks for invalid expressions, missing operands, consecutive operators, and mismatched parentheses.
    - Handles cases where operators are applied after an operand, missing operands for binary operators, and missing truth values for variables.
    - Detects variable definitions in terms of themselves and unrecognized operator symbols.

    Note: Proper error handling is implemented to ensure accurate evaluation of boolean expressions.
*/

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
        return 1;
    case '|':
    case '$':
        return 2;
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
    bool lastWasOperand = false;

    if (expression.empty())
    {
        throw std::invalid_argument("No operands or operators present");
    }

    char prevOp = ' '; // Initialize previous operator with a space character

    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];

        if (isOperator(c))
        {
            if (isOperator(prevOp))
            {
                throw std::invalid_argument("Consecutive operators detected: '" + std::string(1, prevOp) + "' followed by '" + std::string(1, c) + "'");
            }
            prevOp = c;
        }
        else
        {
            prevOp = ' '; // Reset previous operator if the current character is not an operator
        }

        if (c == 'T' || c == 'F')
        {
            operands.push(c == 'T');
            lastWasOperand = true;
        }
        else if (isOperator(c))
        {
            if (c == '!' && lastWasOperand)
            {
                if (!operands.empty() && operands.top())
                {
                    throw std::invalid_argument("NOT operator applied after an operand");
                }
            }
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
            lastWasOperand = false;
        }
        else if (c == '(')
        {
            operators.push(c);
            lastWasOperand = false;
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
                        throw std::invalid_argument("Missing closing parenthesis");
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
            lastWasOperand = true;
        }
        else if (c != ' ')
        {
            if (c == '=')
            {

                throw std::invalid_argument("Variable defined in terms of itself");
            }
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
                throw std::invalid_argument("Missing closing parenthesis");
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
