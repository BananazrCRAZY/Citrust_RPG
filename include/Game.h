#pragma once
#include <string>
#include "Player.h"
//#include "Shop.h"

using std::string;

class Game {
    string gameFile;
    int savePoint;
    int calories;
    Player* player;
    //Shop* shop;

    public:
        Game(string);
        int gameLoop();
        int battleLoop();
        int playerTurn();
        int enemyTurn();
        void turnReset();
        int deathCheck();
        void loadShop();
        void saveGame();
};