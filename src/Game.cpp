#include "include/Game.h"
#include "include/Boss.h"
#include "include/bossHeaders/Apple.h"
#include "include/bossHeaders/Pear.h"
#include "include/bossHeaders/Strawberry.h"
#include "include/bossHeaders/Grape.h"
#include "include/bossHeaders/Dekopon.h"
#include "include/bossHeaders/MangoGreen.h"
#include "include/bossHeaders/MangoRed.h"
#include "include/bossHeaders/Pineapple.h"
#include "include/bossHeaders/Durian.h"
#include "include/bossHeaders/Watermelon.h"
#include "include/Shop.h"
#include "include/button.hpp"
#include "include/ScreenManager.hpp"
#include "include/TitleScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/PrologueScreen1.hpp"
#include <raylib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cerr;
using std::string;
using std::ifstream;
using std::endl;

void Game::uiDraw() {
    BeginDrawing();
    ClearBackground(BLACK);
    screenManager.Draw();
    EndDrawing();
}

void Game::runGame() {
    // Setup!
    InitWindow(1600, 900, "Orange Game");          // window length 1920 x 1080
    SetTargetFPS(60);

    // Boot into title screen
    screenManager.SetScreen(make_unique<TitleScreen>(screenManager, exitGame));

    bool gotFile = false;
    bool gotName = true;
    bool setName = true;
    bool gameLoopReady = false;

    // Game Loop: keep running while window isn't closed and exitGame bool isn't flagged
    while ((WindowShouldClose() == false) && (exitGame == false)) {

        // Notes current mouse position and if mouse is pressed
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        screenManager.Update(mousePosition, mousePressed);

        if (!gotFile) {
            if (screenManager.getInput() == 1 || screenManager.getInput() == 2 || screenManager.getInput() == 3 || screenManager.getInput() == 4) {
                startGame(screenManager.getInput());
                gotFile = true;
                if (savePoint == 0) gotName = false;
                else gameLoopReady = true;
                screenManager.setPlayer(player);
            }
        }
        if (!gotName) {
            if (savePoint == 0) {
                screenManager.ChangeScreen(make_unique<NameScreen>(screenManager, exitGame));
                gotName = true;
                setName = false;
            }
        }
        if (!setName) {
            if (screenManager.GetPlayerName() != "") {
                player->setName(screenManager.GetPlayerName());
                setName = true;
                gameLoopReady = true;
            }
        }
        if (gameLoopReady) {
            gameLoop();
        }
        uiDraw();

    }
    resetGame();
    CloseWindow();
}

void Game::resetGame() {
    delete player;
    delete shop;
}

void Game::openFile(string file) {
    gameFile = file;
    ifstream iFile(gameFile);
    if (!iFile.good()) {
        cerr << "Error with game file fstream\n";
        exit(1);
    }

    iFile >> savePoint;
    iFile >> calories;
    iFile >> playerFile;
    iFile >> playerItemsFile;
    player = new Player(playerFile, playerItemsFile);
    iFile >> shopFile;
    shop = new Shop(shopFile);
}

void Game::startGame(int input) {
    switch (input) {
        case 1:
        case 2:
            // new game
            // load save 1
            openFile("assets/saves/Save1/Game.txt");
            break;
        case 3:
            // load save 2
            openFile("assets/saves/Save2/Game.txt");
            break;
        case 4:
            // load save 3
            openFile("assets/saves/Save3/Game.txt");
            break;
        default:
            cerr << "Game start input error" << endl;
            exit(1);
    }
}

void Game::gameLoop() {
    while (savePoint < 10) {
        // need ui to show screen based on savePoint (dialogue)
        Boss* boss;
        switch (savePoint) {
            case 0:
                screenManager.ChangeScreen(make_unique<PrologueScreen1>(screenManager, exitGame));
                // create boss here, hard code
                boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
                break;
            case 1:
                boss = new Pear("assets/bosses/Pear.txt", "assets/bossItems/PearStem.txt", -1);
                break;
            case 2:
                boss = new Strawberry("assets/bosses/Strawberry.txt", "assets/bossItems/StrawberrySeed.txt", 3);
                break;
            case 3:
                boss = new Grape("assets/bosses/Grape.txt", "assets/bossItems/Grapevine.txt", 3);
                break;
            case 4:
                boss = new Dekopon("assets/bosses/Dekopon.txt", "assets/bossItems/Dekopeel.txt", 3);
                break;
            case 5:
                boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
                break;
            case 6:
                boss = new Pineapple("assets/bosses/Pineapple.txt", "assets/bossItems/PineappleCrown.txt", 1000);
                break;
            case 7:
                boss = new Durian("assets/bosses/Durian.txt", "assets/bossItems/DurianThorn.txt", -1);
                break;
            case 8:
                boss = new Watermelon("assets/bosses/Watermelon.txt", "assets/bossItems/DurianThorn.txt", 1000);
                break;
            default:
                cerr << "Game loop input error" << endl;
                exit(1);
        }
        uiDraw();
        // battleResult: -1 is a loss, if positive then it's the number of cycles
        int battleResult = battleLoop(boss);
        if (savePoint == 5) {
            delete boss;
            boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
            battleResult += battleLoop(boss);
        }
        player->newItem(boss->getItem());
        delete boss;
        //if (battleResult == -1) loadLose();
        int addCalories = player->getLevel() * 1000 / battleResult;
        if (addCalories < 75) addCalories = 75;
        calories += addCalories;
        player->endOfBattle();

        // figure out how to display all objects in shop
        loadInterlude();
        savePoint++;
        saveGame();
    }
}

void Game::loadInterlude() {
    shop->resetShop();
    string printThis;
    while (1) {
        // get input from intermediate screen
        int input;
        switch (input) {
            case 0:
                return;
            case 1:
                printThis = checkBuyItem(0);
                break;
            case 2:
                printThis = checkBuyItem(1);
                break;
            case 3:
                printThis = checkBuyItem(2);
                break;
            case 4:
                printThis = checkBuyItem(3);
                break;
            case 5:
                printThis = checkBuyItem(4);
                break;
            case 6:
                printThis = checkBuyItem(5);
                break;
            case 7:
            // not sure how to equip and unequip items
            default:
                cerr << "Shop loop input error" << endl;
                exit(1);
        }
        // print here

    }
}

// void Game::loadEndOfGame() {
//     resetGame();
//     // have the ui end game screen here and get input
//     int input;
//     switch(input) {
//         case 0:
//             exit(1);
//         case 1:
//             startGame();
//             break;
//         default:
//             break;
//     }
// }

// void Game::loadLose() {
//     resetGame();
//     // have ui load lose screen and get input
//     int input;
//     switch(input) {
//         case 0:
//             exit(1);
//         case 1:
//             startGame();
//             break;
//         default:
//             break;
//     }
// }

int Game::battleLoop(Boss* boss) {
    int battleCycle = 1;
    while (battleCycle < 100) {
        while (player->getTurn() > 0) {
            playerTurn(boss);
            if (player->isDead()) return -1;
            if (boss->isDead()) return battleCycle;
            player->endOfTurn();
            if (player->isDead()) return -1;
        }
        while (boss->getTurn() > 0) {
            enemyTurn(boss);
            if (player->isDead()) return -1;
            if (boss->isDead()) return battleCycle;
            boss->endOfTurn();
            if (boss->isDead()) return battleCycle;
        }
        player->setTurn(1);
        boss->setTurn(1);
        battleCycle++;
    }
    return -1;
}

void Game::playerTurn(Boss* boss) {
    // get input from ui
    int input;
    string print;
    switch (input) {
        case 0:
            print = player->basicAttack(boss);
            break;
        case 1:
            print = player->specialAttack(boss);
            break;
        case 2:
            print = player->useItem(boss, 0);
            break;
        case 3:
            print = player->useItem(boss, 1);
            break;
        case 4:
            print = player->useItem(boss, 2);
            break;
        case 5:
            print = player->useItem(boss, 3);
            break;
        case 6:
            print = player->useItem(boss, 4);
            break;
        case 7:
            print = player->useItem(boss, 5);
            break;
        default:
            cerr << "Player turn input error" << endl;
            exit(1);
    }
    // print out string here

}

void Game::enemyTurn(Boss* boss) {
    string printThis = "";
    if (boss->getBossAbilityCharge() >= boss->getRequiredBossCharge()) {
        printThis += boss->bossAbility() + '\n';   
    }
    
    if (boss->getRechargeCount() >= 1) {
        printThis += boss->specialAttack(player);
    } else {
        printThis += boss->basicAttack(player);
    }
    // print here

}

void Game::saveGame() {
    std::ofstream oFile(gameFile);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << endl;
        exit(1);
    }

    oFile << savePoint << '\n';
    oFile << calories << '\n';
    oFile << playerFile << '\n';
    oFile << playerItemsFile << '\n';
    oFile << shopFile << '\n';

    shop->saveShop();
    player->savePlayer();
}

string Game::checkBuyItem(int index) {
    if (shop->getItemPrice(index) > calories) return "You cannot buy this. You are missing " + std::to_string(shop->getItemPrice(0)-calories) + " calories.";
    return shop->purchaseItem(player, index);
}