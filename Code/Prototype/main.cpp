#include <iostream>
#include <string>
#include <limits>
#include "boolean_logic.h"
#include "truth_tables.h"

int main()
{
    // Main logic for the menu options
    int choice;
    int i = 1;
    std::string expression;
    std::unordered_map<char, bool> variables;

    while (i)
    {
        int h = 1; // Reset h to 1 at the beginning of each iteration

        // Menu options logic
        std::cout << "\033[1;31m\nMenu Options:\033[0m" << std::endl;
        std::cout << "\033[1;32m1. Boolean Logic Calculator\033[0m" << std::endl;
        std::cout << "\033[1;32m2. Truth Table\033[0m" << std::endl;
        std::cout << "\033[1;32m3. Exit\033[0m" << std::endl;

        std::cout << "\033[1;31mEnter your choice: \033[0m";

        // Input verification for integer input
        while (!(std::cin >> choice) || choice < 1 || choice > 3)
        {
            std::cout << "Invalid input. Please input a valid integer between 1 and 3, inclusive." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cin.ignore(); // Ignore newline character

        // Switch case for menu options
        switch (choice)
        {
        case 1:
            while (h)
            {
                // Boolean Logic Calculator logic
                std::cout << "\033[1;32m\nBoolean Logic Calculator\n\033[0m" << std::endl;
                std::cout << "\033[1;31mEnter a Boolean expression or X to go back: \033[0m";
                std::getline(std::cin, expression);
                if (expression == "X" || expression == "x")
                {
                    break; // Exit the inner while loop
                }

                try
                {
                    bool result = evaluateExpression(expression, variables);
                    std::cout << "Expression: " << expression << std::endl;
                    std::cout << "Result: " << (result ? "True" : "False") << std::endl;
                }
                catch (const std::exception &e)
                {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            }
            break;
        case 2:
            // Truth Table logic
            generateTruthTableAND();
            generateTruthTableOR();
            generateTruthTableNOT();
            generateTruthTableNAND();
            generateTruthTableXOR();

            break;
        case 3:
            std::cout << "Exiting the program..." << std::endl;
            i = 0;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}