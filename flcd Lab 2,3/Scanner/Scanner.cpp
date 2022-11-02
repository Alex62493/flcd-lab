//
// Created by Alex on 26.10.2022.
//

#include "Scanner.h"
#include <regex>

std::string strip(const std::string &input)
{
    auto start_it = input.begin();
    auto end_it = input.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

Scanner::Scanner() {
    head = nullptr;
    tail = nullptr;
    identifierSymbolTable = new SymbolTable();
    constantSymbolTable = new SymbolTable();
}

Scanner::~Scanner() {
    LINKED_LIST_NODE* current = head->Flink;
    LINKED_LIST_NODE* last = head;

    while (current) {
        delete last;
        last = current;
        current = current->Flink;
    }
    delete last;

    delete identifierSymbolTable;
    delete constantSymbolTable;
}

int Scanner::startScanning(const std::string& filePath, const std::vector<std::string>& keywords) {
    std::ifstream fin;
    fin.open(filePath, std::ifstream::in);
    int lineNr = 0;

    while (fin.good())
    {
        bool nextIsChar = false;
        bool nextIsString = false;
        char* intermediary = new char[512];
        fin.getline(intermediary, 512);
        std::string line(intermediary);
        delete[] intermediary;
        line = strip(line);

        lineNr++;

        unsigned long long lineLength = line.size();
        unsigned long long positionOnLine = 0;

        while (positionOnLine < lineLength)
        {
            if (line[positionOnLine] == ' ')
            {
                positionOnLine++;
                continue;
            }

            if (isSeparator(line[positionOnLine]))
            {
                std::string token(1, line[positionOnLine]);
                addTokenToPif(token);

                if (line[positionOnLine] == '\'' && positionOnLine + 1 < lineLength) {
                    positionOnLine++;
                    std::string chr = getWord(line, positionOnLine);
                    if (!std::regex_match(chr, std::regex("[a-zA-Z0-9]")))
                        return lineNr;
                    addConstantToPif(chr);
                }

                if (line[positionOnLine] == '\"' && positionOnLine + 1 < lineLength) {
                    positionOnLine++;
                    std::string str = getWord(line, positionOnLine);
                    if (!std::regex_match(str, std::regex("[a-zA-Z0-9]*")))
                        return lineNr;
                    addConstantToPif(str);
                    positionOnLine += str.size() - 1;
                }

                positionOnLine++;
                continue;
            }

            std::string word = getWord(line, positionOnLine);
            unsigned long long final = positionOnLine + word.size();
            bool keywordFound = false;

            for (const std::string& keyword: keywords) {
                if (word == keyword) {
                    keywordFound = true;
                    break;
                }
            }

            if (keywordFound) {
                positionOnLine = final;
                addTokenToPif(word);
                continue;
            }

            if (word == "TRUE" || word == "FALSE") {
                positionOnLine = final;
                addConstantToPif(word);
                continue;
            }

            if (std::regex_match(word, std::regex("[-+]?[1-9][0-9]*")) || word == "0") {
                positionOnLine = final;
                addConstantToPif(word);
                continue;
            }

            if (std::regex_match(word, std::regex("[a-zA-Z][a-zA-Z0-9]*"))) {
                positionOnLine = final;
                addIdentifierToPif(word);
                continue;
            }

            return lineNr;
        }
    }

    fin.close();
    return 0;
}

void Scanner::addTokenToPif(const std::string& token) {
    auto* newNode = new LINKED_LIST_NODE;

    newNode->Flink = nullptr;
    newNode->Blink = tail;
    newNode->name = token;
    newNode->pos = -1;

    tail = newNode;

    if (tail->Blink) {
        tail->Blink->Flink = tail;
    }

    if (!head)
    {
        head = newNode;
    }
}

void Scanner::addIdentifierToPif(const std::string& identifier) {
    auto* newNode = new LINKED_LIST_NODE;

    newNode->Flink = nullptr;
    newNode->Blink = tail;
    newNode->name = "id";
    newNode->pos = identifierSymbolTable->addElementToSymbolTable(identifier);

    tail = newNode;

    if (tail->Blink) {
        tail->Blink->Flink = tail;
    }

    if (!head)
    {
        head = newNode;
    }
}

void Scanner::addConstantToPif(const std::string& constant) {
    auto* newNode = new LINKED_LIST_NODE;

    newNode->Flink = nullptr;
    newNode->Blink = tail;
    newNode->name = "const";
    newNode->pos = constantSymbolTable->addElementToSymbolTable(constant);

    tail = newNode;

    if (tail->Blink) {
        tail->Blink->Flink = tail;
    }

    if (!head)
    {
        head = newNode;
    }
}

bool Scanner::isSeparator(const char element) {
    std::vector<char> separators = {'.', '\'', '\"', '(', ')', '#', ':', ';', ' '};

    for (char a: separators) {
        if (a == element)
            return true;
    }
    return false;
}

std::string Scanner::getWord(std::string line, unsigned long long currentPosition) {
    unsigned long long start = currentPosition;
    unsigned long long final = currentPosition;

    while (final < line.size() && !isSeparator(line[final]))
        final++;

    std::string word = line.substr(start, final - start);
    return word;
}

void Scanner::printResults(const std::string& pifFileName, const std::string& identifierStFile, const std::string& constStFile) {
    std::ofstream fout;
    fout.open(pifFileName, std::ifstream::out);

    LINKED_LIST_NODE* currentNode = head;
    while (currentNode) {
        fout << currentNode->name << " " << currentNode->pos << "\n";
        currentNode = currentNode->Flink;
    }

    fout.close();

    constantSymbolTable->printAllElementsToFile(constStFile);
    identifierSymbolTable->printAllElementsToFile(identifierStFile);
}
