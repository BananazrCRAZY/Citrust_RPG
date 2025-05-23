#pragma once
#include <string>
#include "Player.h"
#include "Boss.h"
//#include "Shop.h"

using std::string;

class Game {
    string gameFile;
    int savePoint;
    int calories;
    Player* player;
    //Shop* shop;
    string bossList;

    public:
        Game(string);
        int gameLoop();
        string getBossFile();
        int battleLoop(Boss*);
        int playerTurn(Boss*);
        int enemyTurn();
        void turnReset();
        int deathCheck();
        void loadShop();
        void saveGame();
};