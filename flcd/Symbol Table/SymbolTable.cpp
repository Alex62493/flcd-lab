//
// Created by Alex on 19.10.2022.
//

#include "SymbolTable.h"
//1b

SymbolTable::SymbolTable() {
    startNode = nullptr;
    size = 0;
}

long long SymbolTable::checkForExistingNode(const std::string& name) {
    SYMBOL_TABLE_NODE* currentNode = startNode;
    long long pos = 1;

    while (currentNode)
    {
        if (name == currentNode->name)
        {
            return pos;
        }
        else if (name < currentNode->name)
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

long long SymbolTable::addElementToSymbolTable(const std::string& name) {
    SYMBOL_TABLE_NODE* lastNode = nullptr;
    SYMBOL_TABLE_NODE* currentNode = startNode;
    long long pos = 1;
    long long existingPos = checkForExistingNode(name);

    if (existingPos)
    {
        return existingPos;
    }

    while (currentNode) {
        lastNode = currentNode;

        if (name < currentNode->name)
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

    node->name = name;

    node->right = nullptr;
    node->left = nullptr;

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
