#include <iostream>
#include "Scanner/Scanner.h"

int main() {
    Scanner scanner;

    std::ifstream fin;
    fin.open("tokens.in", std::ifstream::in);

    std::vector<std::string> keywords;

    while (fin.good())
    {
        std::string word;
        fin >> word;
        keywords.emplace_back(word);
    }

    int returnCode = scanner.startScanning("p.txt", keywords);

    if (returnCode)
        std::cout << returnCode;
    else
        scanner.printResults("pif.txt", "stide.txt", "stcon.txt");

    return 0;
}
