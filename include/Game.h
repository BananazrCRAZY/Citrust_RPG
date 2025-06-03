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
    void gameLoop();
    void loadInterlude();
    void loadEndOfGame();
    void loadLose();
    void saveGame();
    string getBossFile() const;
    string getDialogueFile() const;
    int battleLoop(Boss*);
    void playerTurn(Boss*);
    void enemyTurn(Boss*);
    void openFile(string);
    string checkBuyItem(int);
    void resetGame();

    public:
        Game() {}
        ~Game() { resetGame(); }
        void runGame() {
            startGame();
            // get ui to send name
            string inputName;
            player->setName(inputName);
            gameLoop();
            loadEndOfGame();
        }
};
