#ifndef FLCD_SYMBOLTABLE_H
#define FLCD_SYMBOLTABLE_H

#include <cstring>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

struct SYMBOL_TABLE_NODE {
    std::string name;
    SYMBOL_TABLE_NODE* left;
    SYMBOL_TABLE_NODE* right;
};

class SymbolTable {
private:
    int size;
    SYMBOL_TABLE_NODE* startNode;

    long long checkForExistingNode(const std::string& name);
    void printNode(SYMBOL_TABLE_NODE* node, std::vector<std::pair<std::string, long long>>& elements);

public:
    SymbolTable();

    long long addElementToSymbolTable(const std::string& name);
    void printAllElementsToFile(const std::string& file);
};


#endif //FLCD_SYMBOLTABLE_H
