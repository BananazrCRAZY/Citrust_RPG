#pragma once
#include <string>
#include "Player.h"

using std::string;

class UI {
    int input;
    public:
        UI() : input(0) {}
        int startMenu();
        void printDialogue(string);
        int playerAction(Player*);
        void print(string o);
        string orangeCreate();
};