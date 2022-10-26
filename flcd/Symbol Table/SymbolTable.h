#ifndef FLCD_SYMBOLTABLE_H
#define FLCD_SYMBOLTABLE_H

#include <cstring>
#include <string>

/*
enum VALUE_TYPE {
    BOOL,
    INT,
    CHAR,
    STRING
};

union VALUE{
    int intVal;
    bool boolVal;
    char charVal;
    char* stringVal;
};
*/

struct SYMBOL_TABLE_NODE {
    std::string name;
    SYMBOL_TABLE_NODE* left;
    SYMBOL_TABLE_NODE* right;
    //VALUE_TYPE valueType;
    //VALUE value;
};

class SymbolTable {
private:
    int size;
    SYMBOL_TABLE_NODE* startNode;

    long long checkForExistingNode(const std::string& name);

public:
    SymbolTable();

    long long addElementToSymbolTable(const std::string& name);
};


#endif //FLCD_SYMBOLTABLE_H
