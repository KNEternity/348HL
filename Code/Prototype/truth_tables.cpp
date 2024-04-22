#include <iostream>

// Function to generate truth table for logical AND operation
void generateTruthTableAND()
{
    std::cout << "Truth Table for Logical AND Operation" << std::endl;
    std::cout << "A\tB\tResult" << std::endl;
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
    std::cout << "Truth Table for Logical OR Operation" << std::endl;
    std::cout << "A\tB\tResult" << std::endl;
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
    std::cout << "Truth Table for Logical NOT Operation" << std::endl;
    std::cout << "A\tResult" << std::endl;
    for (char a : {'T', 'F'})
    {
        std::cout << a << "\t" << (a == 'T' ? 'F' : 'T') << std::endl;
    }
    std::cout << std::endl;
}

// Function to generate truth table for logical NAND operation
void generateTruthTableNAND()
{
    std::cout << "Truth Table for Logical NAND Operation" << std::endl;
    std::cout << "A\tB\tResult" << std::endl;
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
    std::cout << "Truth Table for Logical XOR Operation" << std::endl;
    std::cout << "A\tB\tResult" << std::endl;
    for (char a : {'T', 'F'})
    {
        for (char b : {'T', 'F'})
        {
            std::cout << a << "\t" << b << "\t" << ((a == 'T' || b == 'T') && !(a == 'T' && b == 'T') ? 'T' : 'F') << std::endl;
        }
    }
    std::cout << std::endl;
}
