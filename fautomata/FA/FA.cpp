//
// Created by Alex on 09.11.2022.
//

#include "FA.h"

#include <utility>
#include <sstream>

FA::FA(const std::string& fileName) {
    readFromFile(fileName);
}

void FA::split(const std::string& s, std::vector<std::string> &list, const char del) {
    std::stringstream ss(s);
    std::string word;
    while (!ss.eof()) {
        getline(ss, word, del);
        list.emplace_back(word);
    }
}

void FA::readFromFile(const std::string& fileName) {
    std::ifstream fin;
    fin.open(fileName, std::ifstream::in);

    char* intermediary = new char[512];
    fin.getline(intermediary, 512);
    std::string state(intermediary);
    delete[] intermediary;

    split(state, states);

    intermediary = new char[512];
    fin.getline(intermediary, 512);
    std::string alph(intermediary);
    delete[] intermediary;

    split(alph, alphabet);

    intermediary = new char[512];
    fin.getline(intermediary, 512);
    initialState = intermediary;
    delete[] intermediary;

    intermediary = new char[512];
    fin.getline(intermediary, 512);
    std::string fStates(intermediary);
    delete[] intermediary;

    split(fStates, finalStates);

    while (fin.good()) {
        TRANSITION transition;

        fin >> transition.startState >> transition.path >> transition.finalState;
        transitions.emplace_back(transition);
    }

    fin.close();
}

void FA::listInitialState() {
    std::cout << initialState << "\n";
}

void FA::listFinalStates() {
    std::cout << "Final states:\n";

    for (const std::string& state : finalStates) {
        std::cout << state << "\n";
    }
}

void FA::listStates() {
    std::cout << "States:\n";

    for (const std::string& state : states) {
        std::cout << state << "\n";
    }
}

void FA::listAlphabet() {
    std::cout << "Alphabet:\n";

    for (const std::string& a : alphabet) {
        std::cout << a << "\n";
    }
}

void FA::listTransitions() {
    std::cout << "Transitions:\n";

    for (TRANSITION transition : transitions) {
        std::cout << "(" << transition.startState << ", " << transition.path << ") = " << transition.finalState << "\n";
    }
}

bool FA::checkDFA(const std::string& path, bool& result) {
    std::vector<std::string> p;
    split(path, p);

    std::string currentState = initialState;
    result = false;

    for (const std::string& a: p) {
        std::string nextState;

        for (const TRANSITION& b: transitions) {
            if (b.startState == currentState && b.path == a) {
                if (nextState.empty())
                    nextState = b.finalState;
                else
                    return false;
            }
        }

        if (nextState.empty())
            return false;

        currentState = nextState;
    }

    for (const std::string& a: finalStates) {
        if (a == currentState) {
            result = true;
            return true;
        }
    }

    return true;
}




