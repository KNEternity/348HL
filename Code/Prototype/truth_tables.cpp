#include <iostream>
#include "truth_tables.h"
// Function to generate truth table for logical AND operation
void generateTruthTableAND()
{
    std::cout << "Truth Table for Logical \033[1;32mAND\033[0m Operation" << std::endl;
    std::cout << "\033[1;32mA\tB\tResult\033[0m" << std::endl;
    for (char a : {'T', 'F'})
    {
        for (char b : {'T', 'F'})
        {
            std::cout << a << "\t" << b << "\t" << (a == 'T' && b == 'T' ? 'T' : 'F') << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function to generate truth table for logical OR operation
void generateTruthTableOR()
{
    std::cout << "Truth Table for Logical \033[1;32mOR\033[0m Operation" << std::endl;
    std::cout << "\033[1;32mA\tB\tResult\033[0m" << std::endl;
    for (char a : {'T', 'F'})
    {
        for (char b : {'T', 'F'})
        {
            std::cout << a << "\t" << b << "\t" << (a == 'T' || b == 'T' ? 'T' : 'F') << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function to generate truth table for logical NOT operation
void generateTruthTableNOT()
{
    std::cout << "Truth Table for Logical \033[1;32mNOT\033[0m Operation" << std::endl;
    std::cout << "\033[1;32mA\tResult\033[0m" << std::endl;
    for (char a : {'T', 'F'})
    {
        std::cout << a << "\t" << (a == 'T' ? 'F' : 'T') << std::endl;
    }
    std::cout << std::endl;
}

// Function to generate truth table for logical NAND operation
void generateTruthTableNAND()
{
    std::cout << "Truth Table for Logical \033[1;32mNAND\033[0m Operation" << std::endl;
    std::cout << "\033[1;32mA\tB\tResult\033[0m" << std::endl;
    for (char a : {'T', 'F'})
    {
        for (char b : {'T', 'F'})
        {
            std::cout << a << "\t" << b << "\t" << (a == 'T' && b == 'T' ? 'F' : 'T') << std::endl;
        }
    }
    std::cout << std::endl;
}

// Function to generate truth table for logical XOR operation
void generateTruthTableXOR()
{
    std::cout << "Truth Table for Logical \033[1;32mXOR\033[0m Operation" << std::endl;
    std::cout << "\033[1;32mA\tB\tResult\033[0m" << std::endl;
    for (char a : {'T', 'F'})
    {
        for (char b : {'T', 'F'})
        {
            std::cout << a << "\t" << b << "\t" << ((a == 'T' || b == 'T') && !(a == 'T' && b == 'T') ? 'T' : 'F') << std::endl;
        }
    }
    std::cout << std::endl;
}