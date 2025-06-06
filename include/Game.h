#pragma once
#include <string>
#include "Player.h"
#include "Boss.h"
#include "Shop.h"

using std::string;

class Game {
    string gameFile;
    int savePoint;
    int calories;
    Player* player;
    Shop* shop;
    string playerFile;
    string playerItemsFile;
    string shopFile;

    void startGame();
    void gameLoop();
    void loadInterlude();
    void loadEndOfGame();
    void loadLose();
    void saveGame();
    int battleLoop(Boss*);
    void playerTurn(Boss*);
    void enemyTurn(Boss*);
    void openFile(string);
    string checkBuyItem(int);
    void resetGame();

    public:
        Game() : player(nullptr), shop(nullptr) {}
        ~Game() { resetGame(); }
        void runGame();
};
