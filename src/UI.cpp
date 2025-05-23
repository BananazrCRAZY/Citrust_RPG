#include "UI.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

using std::string;
using std::cout;
using std::cin;
using std::ifstream;
using std::cerr;

int UI::startMenu() {
    start_label:
    cout << "PLAY  CONTINUE  QUIT\n";
    cin >> input;
    if (input == 2) return 0;
    if (input == 0) return 1;
    if (input == 1) {
        cout << "SAVE1  SAVE2  SAVE3  BACK\n";
        if (input == 0) return 2;
        if (input == 1) return 3;
        if (input == 2) return 4;
        else goto start_label;
    }
}

void UI::printDialogue(string file) {
    ifstream iFile(file);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    char output;
    while (iFile.get(output)) {
        if (output == '=') {
            // be able to print character name
            continue;
        }
        // add a delay here for typewriter effect
        cout << output;
    }
    iFile.close();
}

int UI::playerAction(Player* player) {
    action_label:
    cout << "BASIC_ATTACK  SPECIAL_ATTACK  ITEMS\n";
    cin >> input;
    if (input == 0) return 0;
    if (input == 1) return 1;
    else {
        player->printItems();
        cout << "  BACK\n";
        if (input == 6) goto action_label;
        int input2 = 0;
        cout << "SELF  BOSS\n";
        cin >> input2;
        if (input == 0 && input2 == 0) return 2;
        if (input == 1 && input2 == 0) return 3;
        if (input == 2 && input2 == 0) return 4;
        if (input == 3 && input2 == 0) return 5;
        if (input == 4 && input2 == 0) return 6;
        if (input == 5 && input2 == 0) return 7;
        if (input == 0 && input2 == 1) return 8;
        if (input == 1 && input2 == 1) return 9;
        if (input == 2 && input2 == 1) return 10;
        if (input == 3 && input2 == 1) return 11;
        if (input == 4 && input2 == 1) return 12;
        if (input == 5 && input2 == 1) return 13;
    }
}
