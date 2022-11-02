//
// Created by Alex on 26.10.2022.
//

#ifndef FLCD_SCANNER_H
#define FLCD_SCANNER_H

#include "../Symbol Table/SymbolTable.h"

struct LINKED_LIST_NODE {
    LINKED_LIST_NODE* Flink;
    LINKED_LIST_NODE* Blink;
    std::string name;
    long long pos;
};

class Scanner {
private:
    LINKED_LIST_NODE* head;
    LINKED_LIST_NODE* tail;
    SymbolTable* identifierSymbolTable;
    SymbolTable* constantSymbolTable;

    void addTokenToPif(const std::string& token);
    void addIdentifierToPif(const std::string& identifier);
    void addConstantToPif(const std::string& constant);
    static bool isSeparator(const char element);
    static std::string getWord(std::string line, unsigned long long currentPosition);

public:
    Scanner();
    ~Scanner();

    int startScanning(const std::string& filePath, const std::vector<std::string>& keywords);
    void printResults(const std::string& pifFileName, const std::string& identifierStFile, const std::string& constStFile);
};


#endif //FLCD_SCANNER_H
