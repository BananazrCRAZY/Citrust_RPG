#pragma once
#include "include/Buttons/button.hpp"
#include "include/Screens/ScreenManager.hpp"
#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/NameScreen.hpp"
#include "include/Popups/Popup.hpp"
#include <string>
#include "include/Objects/Player.h"
#include "include/bossHeaders/Boss.h"
#include "include/Objects/Shop.h"

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
    int loadEndOfGame();
    void saveGame();
    int battleLoop(Boss*);
    void playerTurn(Boss*);
    void enemyTurn(Boss*);
    string checkBuyItem(int);
    void resetGame();
    void uiDraw();
    void resetSave();
    bool isNewSave(string);

    public:
        Game();
        ~Game() { resetGame(); }
        void runGame();
        void openFile(string);
};
