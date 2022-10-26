#ifndef FLCD_SYMBOLTABLE_H
#define FLCD_SYMBOLTABLE_H

#include <cstring>

enum VALUE_TYPE {
    BOOL,
    INT,
    CHAR,
    STRING,
    NONE
};

union VALUE{
    int intVal;
    bool boolVal;
    char charVal;
    char* stringVal;
};

struct SYMBOL_TABLE_NODE {
    char* name;
    SYMBOL_TABLE_NODE* left;
    SYMBOL_TABLE_NODE* right;
    VALUE_TYPE valueType;
    VALUE value;
};

class SymbolTable {
private:
    int size;
    SYMBOL_TABLE_NODE* startNode;

    long long checkForExistingNode(char* name, SYMBOL_TABLE_NODE* &node);

public:
    SymbolTable();

    long long addElementToSymbolTable(char* name, VALUE_TYPE type, VALUE value);
};


#endif //FLCD_SYMBOLTABLE_H
