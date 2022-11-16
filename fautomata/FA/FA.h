//
// Created by Alex on 09.11.2022.
//

#ifndef FA_FA_H
#define FA_FA_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct TRANSITION {
    std::string startState;
    std::string path;
    std::string finalState;
};

class FA {
private:
    std::string initialState;
    std::vector<std::string> finalStates;
    std::vector<std::string> states;
    std::vector<std::string> alphabet;
    std::vector<TRANSITION> transitions;

    void readFromFile(const std::string& fileName);
    static void split(const std::string& s, std::vector<std::string> &list, const char del = ' ');

public:
    explicit FA(const std::string& fileName);
    void listInitialState();
    void listFinalStates();
    void listStates();
    void listAlphabet();
    void listTransitions();

    bool checkDFA(const std::string& path, bool& result);
};


#endif //FA_FA_H
