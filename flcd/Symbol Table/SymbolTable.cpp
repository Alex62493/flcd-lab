//
// Created by Alex on 19.10.2022.
//

#include "SymbolTable.h"
//1b

SymbolTable::SymbolTable() {
    startNode = nullptr;
    size = 0;
}

long long SymbolTable::checkForExistingNode(char *name, SYMBOL_TABLE_NODE* &node) {
    SYMBOL_TABLE_NODE* currentNode = startNode;
    long long pos = 1;
    node = nullptr;

    while (currentNode)
    {
        int compareValue = std::strcmp(name, currentNode->name);
        if (compareValue == 0)
        {
            return pos;
            node = currentNode;
        }
        else if (compareValue < 0)
        {
            pos <<= 1;
            currentNode = currentNode->left;
        }
        else
        {
            pos <<= 1;
            pos++;
            currentNode = currentNode->right;
        }
    }
    return 0;
}

long long SymbolTable::addElementToSymbolTable(char *name, VALUE_TYPE type, VALUE value) {
    SYMBOL_TABLE_NODE* lastNode = nullptr;
    SYMBOL_TABLE_NODE* currentNode = startNode;
    SYMBOL_TABLE_NODE* existingNode = nullptr;
    long long pos = 1;
    long long existingPos = checkForExistingNode(name, existingNode);

    if (existingPos && existingNode)
    {
        if (type != NONE)
            existingNode->value = value;
        return existingPos;
    }

    while (currentNode) {
        lastNode = currentNode;

        int compareValue = std::strcmp(name, currentNode->name);

        if (compareValue < 0)
        {
            pos *= 2;
            currentNode = currentNode->left;
        }
        else
        {
            pos = pos * 2 + 1;
            currentNode = currentNode->right;
        }
    }

    auto* node = new SYMBOL_TABLE_NODE;

    node->name = new char[std::strlen(name) + 1];
    std::strcpy(node->name, name);

    node->right = nullptr;
    node->left = nullptr;
    node->valueType = type;
    node->value = value;

    if (lastNode)
    {
        if (pos & 1)
        {
            lastNode->right = node;
        }
        else
        {
            lastNode->left = node;
        }
    }
    else
    {
        startNode = node;
    }

    return pos;
}
