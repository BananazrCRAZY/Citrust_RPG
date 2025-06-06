#pragma once
#include "include/button.hpp"
#include "include/ScreenManager.hpp"
#include "include/TitleScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/Popup.hpp"
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
    ScreenManager screenManager;
    bool exitGame;

    void startGame(int input);
    int gameLoop();
    void loadInterlude();
    void loadEndOfGame();
    void loadLose();
    void saveGame();
    int battleLoop(Boss*);
    void playerTurn(Boss*);
    void enemyTurn(Boss*);
    string checkBuyItem(int);
    void resetGame();
    void uiDraw();

    public:
        Game();
        ~Game() { resetGame(); }
        void runGame();
        void openFile(string);
};
