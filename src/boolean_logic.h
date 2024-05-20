#ifndef BOOLEAN_LOGIC_H
#define BOOLEAN_LOGIC_H

#include <string>
#include <unordered_map>

bool AND(bool a, bool b);
bool OR(bool a, bool b);
bool NOT(bool a);
bool NAND(bool a, bool b);
bool XOR(bool a, bool b);
int getPrecedence(char op);
bool isOperator(char op);
bool evaluateExpression(const std::string &expression, const std::unordered_map<char, bool> &variables);

#endif // BOOLEAN_LOGIC_H
