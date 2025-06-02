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
    string bossList;
    string dialogueList;
    string playerFile;
    string playerItemsFile;
    string shopFile;

    void startGame();
    int gameLoop();
    void loadShop();
    void saveGame();
    string getBossFile() const;
    string getDialogueFile() const;
    int battleLoop(Boss*);
    void playerTurn(Boss*);
    void enemyTurn(Boss*);
    void openFile(string);

    public:
        Game() {}
        void runGame() {
            startGame();
            // get ui to send name
            string inputName;
            player->setName(inputName);
            gameLoop();
        }
};
