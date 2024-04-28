#include <iostream>
#include <string>
#include "boolean_logic.cpp"
#include "truth_tables.cpp"

int main()
{
    // Main logic for the menu options
    int choice;
    int i = 1;
    std::string expression;
    std::unordered_map<char, bool> variables;

    while (i)
    {
        // Menu options logic
        std::cout << "\033[1;31m\nMenu Options:\033[0m" << std::endl;
        std::cout << "\033[1;32m1. Boolean Logic Calculator\033[0m" << std::endl;
        std::cout << "\033[1;32m2. Truth Table\033[0m" << std::endl;
        std::cout << "\033[1;32m3. Exit\033[0m" << std::endl;

        std::cout << "\033[1;31mEnter your choice: \033[0m";
        std::cin >> choice;
        std::cin.ignore(); // Ignore newline character

        // Switch case for menu options
        switch (choice)
        {
        case 1:
            // Boolean Logic Calculator logic
            std::cout << "\033[1;32m\nBoolean Logic Calculator\n\033[0m" << std::endl;
            std::cout << "\033[1;31mEnter a Boolean expression or type X to exit: \033[0m";
            std::getline(std::cin, expression);

            if (expression != "X" && expression != "x")
            {
                bool result = evaluateExpression(expression, variables);
                std::cout << "Expression: " << expression << std::endl;
                std::cout << "Result: " << (result ? "True" : "False") << std::endl;
            }
            else
            {
                i = 0;
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
            break;
        }
    }

    return 0;
}
