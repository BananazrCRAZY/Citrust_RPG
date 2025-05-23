#pragma once
#include <string>

using std::string;

class UI {
    int input;
    public:
        UI() : input(0) {}
        int startMenu();
        void printDialogue(string);
};