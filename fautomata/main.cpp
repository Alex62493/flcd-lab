#include <iostream>
#include "FA/FA.h"

void printMenu() {
    std::cout << "Functions:\n";
    std::cout << "1. States\n";
    std::cout << "2. Initial State\n";
    std::cout << "3. Final States\n";
    std::cout << "4. Alphabet\n";
    std::cout << "5. Transitions\n";
    std::cout << "6. Check DFA\n";
    std::cout << "7. Exit\n";
}

int main() {
    FA fa("FA.in");

    while (true) {
        std::string f;
        printMenu();
        std::cout << ">> ";
        std::cin >> f;
        if (f == "1") {
            fa.listStates();
        }
        else if (f == "2")
            fa.listInitialState();
        else if (f == "3")
            fa.listFinalStates();
        else if (f == "4")
            fa.listAlphabet();
        else if (f == "5")
            fa.listTransitions();
        else if (f == "6") {
            std::cout << "Path: ";
            std::string path;
            bool result;
            std::getline(std::cin, path);
            std::getline(std::cin, path);

            if (!fa.checkDFA(path, result))
                std::cout << "Not a DFA!\n";
            else{
                if (result)
                    std::cout << "Good!\n";
                else
                    std::cout << "Bad!\n";
            }
        }
        else if (f == "7")
            break;
        else
            std::cout << "Bad Input!";

        std ::cout << "\n";
    }

    return 0;
}
