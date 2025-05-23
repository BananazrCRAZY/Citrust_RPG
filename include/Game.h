#pragma once
#include <string>
#include "Player.h"
#include "Boss.h"
//#include "Shop.h"
#include "UI.h"

using std::string;

class Game {
    string gameFile;
    int savePoint;
    int calories;
    Player* player;
    //Shop* shop;
    string bossList;
    string dialogueList;
    UI ui;

    public:
        Game() {}
        void openFile(string);
        void startGame();
        int gameLoop();
        string getBossFile() const;
        string getDialogueFile() const;
        int battleLoop(Boss*);
        int playerTurn(Boss*);
        int enemyTurn();
        void turnReset();
        int deathCheck();
        void loadShop();
        void saveGame();
};