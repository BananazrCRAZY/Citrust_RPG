#include "include/Objects/Game.h"
#include "include/bossHeaders/Boss.h"
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
#include "include/Objects/Shop.h"
#include "include/Buttons/button.hpp"
#include "include/Screens/AppleBossScreen.hpp"
#include "include/Screens/InterludeScreen.hpp"
#include "include/Screens/LoseScreen.hpp"
#include "include/Screens/NameScreen.hpp"
#include "include/Screens/PrologueScreen1.hpp"
#include "include/Screens/ScreenManager.hpp"
#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/WinScreen.hpp"
#include <raylib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <unistd.h>

using std::cerr;
using std::string;
using std::ifstream;
using std::endl;

Game::Game() : savePoint(-1), player(nullptr), shop(nullptr), exitGame(false) {
    // Setup!
    InitWindow(1600, 900, "Citrust RPG");          // window length 1920 x 1080
    SetTargetFPS(60);

    // Boot into title screen
    screenManager.PushScreen(make_unique<TitleScreen>(screenManager, exitGame));
}

void Game::uiDraw() {
    // Notes current mouse position and if mouse is pressed
    Vector2 mousePosition = GetMousePosition();
    bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
    screenManager.Update(mousePosition, mousePressed);

    BeginDrawing();
    ClearBackground(BLACK);
    screenManager.Draw();
    EndDrawing();
}

void Game::runGame() {
    resetGame();
    screenManager.ChangeScreen(make_unique<TitleScreen>(screenManager, exitGame));

    bool gotFile = false;
    bool setName = true;
    bool gameLoopReady = false;
    int winGame = 0;
    screenManager.setInput(-1);

    // Game Loop: keep running while window isn't closed and exitGame bool isn't flagged
    while ((WindowShouldClose() == false) && (!exitGame)) {
        uiDraw();

        // // Notes current mouse position and if mouse is pressed
        // Vector2 mousePosition = GetMousePosition();
        // bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        // screenManager.Update(mousePosition, mousePressed);

        if (!gotFile) {
            // 1: new game -> loads save 1
            // 2, 3, 4: loads save 1, 2, 3
            // 5, 6, 7: delete save 1, 2, 3
            switch(screenManager.getInput()) {
                case -1:
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    startGame(screenManager.getInput());
                    gotFile = true;
                    if (savePoint == 0) {
                        screenManager.ChangeScreen(make_unique<NameScreen>(screenManager, exitGame));
                        setName = false;
                    }
                    screenManager.setPlayer(player);
                    screenManager.AddBossCount(savePoint);
                    break;
                case 5:
                    openFile("assets/saves/Save1/Game.txt");
                    resetSave();
                    break;
                case 6:
                    openFile("assets/saves/Save2/Game.txt");
                    resetSave();
                    break;
                case 7:
                    openFile("assets/saves/Save3/Game.txt");
                    resetSave();
                    break;
                default:
                    cerr << "Error: runGame(), if !gotFile, switch case, sm input error" << endl;
                    exit(1);
            }
            screenManager.setInput(-1);
        }
        if (!setName) {
            if (screenManager.GetPlayerName() != "") {
                player->setName(screenManager.GetPlayerName());
                setName = true;
                gameLoopReady = true;
            }
        }
        if (gameLoopReady || savePoint > 0) {
            winGame = gameLoop();
            switch (winGame) {
                case -1:
                    // exit game
                    exitGame = true;
                    break;
                case 0:
                    // return to main menu
                    resetGame();
                    gotFile = false;
                    setName = true;
                    gameLoopReady = false;
                    break;
                case 1:
                    // try again
                    break;
                default:
                    cerr << "Error: winGame contains unknown value" << endl;
                    exit(1);
            }
        }
    }
    resetGame();
    CloseWindow();
}

void Game::resetGame() {
    delete player;
    player = nullptr;
    delete shop;
    shop = nullptr;
    savePoint = -10000000;
    screenManager.SetPlayerName("");
}

void Game::openFile(string file) {
    resetGame();
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

bool Game::isNewSave(string file) {
    ifstream iFile(file);
    if (!iFile.good()) {
        cerr << "Error: opening file isNewSave()";
        exit(1);
    }
    iFile >> savePoint;
    return savePoint == 0;
}

void Game::startGame(int input) {
    switch (input) {
        case 1:
            if (isNewSave("assets/saves/Save1/Game.txt")) {
                openFile("assets/saves/Save1/Game.txt");
                break;
            } else if (isNewSave("assets/saves/Save2/Game.txt")) {
                openFile("assets/saves/Save2/Game.txt");
                break;
            } else if (isNewSave("assets/saves/Save3/Game.txt")) {
                openFile("assets/saves/Save3/Game.txt");
                break;
            }
        case 2:
            // if there is no new game
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
            cerr << "Error: startGame() input unknown" << endl;
            exit(1);
    }
}

int Game::gameLoop() {
    Boss* boss = nullptr;
    player->endOfBattle();
    while (!exitGame) {
        // need ui to show screen based on savePoint (dialogue)
        switch (savePoint) {
            case 0:
                boss = new Apple("assets/bosses/Apple.txt", "assets/bossItems/AppleCore.txt", -1);
                screenManager.ChangeScreen(make_unique<PrologueScreen1>(screenManager, exitGame));
                break;
            case 1:
                boss = new Pear("assets/bosses/Pear.txt", "assets/bossItems/PearStem.txt", -1);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 2:
                boss = new Strawberry("assets/bosses/Strawberry.txt", "assets/bossItems/StrawberrySeed.txt", 3);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 3:
                boss = new Grape("assets/bosses/Grape.txt", "assets/bossItems/Grapevine.txt", 4);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 4:
                boss = new Dekopon(playerFile, "assets/bossItems/Dekopeel.txt", 3);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 5:
                boss = new MangoGreen("assets/bosses/MangoGreen.txt", "assets/bossItems/DriedMango.txt", -1);
                delete boss->getItem();
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 7:
                boss = new Pineapple("assets/bosses/Pineapple.txt", "assets/bossItems/PineappleCrown.txt", 1000);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 8:
                boss = new Durian("assets/bosses/Durian.txt", "assets/bossItems/DurianThorn.txt", -1);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            case 9:
                boss = new Watermelon("assets/bosses/Watermelon.txt", "assets/bossItems/DurianThorn.txt", 1000);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                break;
            default:
                cerr << "Game loop input error" << endl;
                exit(1);
        }
        screenManager.setBoss(boss);
        uiDraw();
        // battleResult: -1 is a loss, if positive then it's the number of cycles
        int battleResult = battleLoop(boss);
        if (savePoint == 5) {
            if (battleResult != -1) {
                // if player used special attack to defeat phase 1
                if (screenManager.getInput() == 1) player->setRechargeCount(1);
                delete boss;
                savePoint++;
                boss = new MangoRed("assets/bosses/MangoRed.txt", "assets/bossItems/DriedMango.txt", -1);
                screenManager.setBoss(boss);
                screenManager.AddBossCount(1);
                screenManager.ChangeScreen(make_unique<AppleBossScreen>(screenManager, exitGame));
                uiDraw();
                int battleResult2 = battleLoop(boss);
                if (battleResult2 == -1) goto lose;
                battleResult += battleResult2;
            }
        }
        if (battleResult == -1) {
            lose:
            if (savePoint != 5) delete boss->getItem();

            screenManager.ChangeScreen(make_unique<LoseScreen>(screenManager));
            delete boss;
            boss = nullptr;

            return loadEndOfGame();
        }
        player->newItem(boss->getItem());

        // load win screen here

        delete boss;
        boss = nullptr;
        int addCalories = player->getLevel() * 550 / battleResult;
        if (addCalories < 75) addCalories = 75;
        calories += addCalories;
        player->levelUp();
        player->endOfBattle();
        screenManager.AddBossCount(1);

        // end of game
        if (savePoint == 9) {
            screenManager.ChangeScreen(make_unique<LoseScreen>(screenManager));
            return loadEndOfGame();
        }

        loadInterlude();
        savePoint++;
        saveGame();
    }
    return 0;
}

void Game::loadInterlude() {
    shop->resetShop();
    screenManager.setShopItems(shop->getItemsForSale());
    screenManager.ChangeScreen(make_unique<InterludeScreen>(screenManager, exitGame, player));
    string printThis;
    while (1) {
        screenManager.setInput(-1);
        screenManager.setCalories(calories);
        // load interlude screen here
        while(screenManager.getInput() == -1) uiDraw();
        int inputNum = screenManager.getInput();
        if (inputNum >= 8 && inputNum < (14 + player->getNumberInventoryItems())) {
            if (inputNum < 14) {
                printThis = "Unequipped " + player->getBattleItem(inputNum-8)->getName();
                player->unequipItem(inputNum-8);
            } else {
                printThis = "Equipped " + player->getInventoryItem(inputNum-14)->getName();
                player->equipItem(inputNum-14);
            }
        } else {
            switch (inputNum) {
                case 0:
                    exitGame = true;
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
                    return;
                default:
                    cerr << "Shop loop input error" << endl;
                    exit(1);
            }
        }
        // print here

    }
}

int Game::loadEndOfGame() {
    screenManager.setInput(-1);
    uiDraw();
    while(screenManager.getInput() == -1) uiDraw();
    switch(screenManager.getInput()) {
        case 0:
            // exit game
            return -1;
        case 1:
            // return to main menu
            return 0;
        case 2:
            // try again
            return 1;
        default:
            cerr << "load lose input error" << endl;
            exit(1);
    }
}

int Game::battleLoop(Boss* boss) {
    int battleCycle = 1;
    while (battleCycle < 100) {
        screenManager.setInput(-1);
        while (player->getTurn() > 0 && !screenManager.isPopup()) {
            uiDraw();
            playerTurn(boss);
            if (player->isDead()) return -1;
            if (boss->isDead()) return battleCycle;
            player->endOfTurn();
            if (player->isDead()) return -1;
            uiDraw();
        }
        while (boss->getTurn() > 0 && !screenManager.isPopup()) {
            uiDraw();
            enemyTurn(boss);
            if (player->isDead()) return -1;
            if (boss->isDead()) return battleCycle;
            boss->endOfTurn();
            if (boss->isDead()) return battleCycle;
            uiDraw();
        }
        if (player->getTurn() <= 0 && boss->getTurn() <= 0 && !screenManager.isPopup()) {
            player->setTurn(1);
            boss->setTurn(1);
            battleCycle++;
        }
        uiDraw();
    }
    return -1;
}

void Game::playerTurn(Boss* boss) {
    redoTurn:
    screenManager.setInput(-1);
    while (screenManager.getInput() == -1) uiDraw();
    switch (screenManager.getInput()) {
        case 0:
            screenManager.ShowPopup(player->basicAttack(boss));
            break;
        case 1:
            if (player->getRechargeCount() <= 0) {
                screenManager.ShowPopup("Not Enough Skill Points");
                goto redoTurn;
            }
            screenManager.ShowPopup(player->specialAttack(boss));
            break;
        case 2:
            screenManager.ShowPopup(player->useItem(boss, 0));
            goto redoTurn;
        case 3:
            screenManager.ShowPopup(player->useItem(boss, 1));
            goto redoTurn;
        case 4:
            screenManager.ShowPopup(player->useItem(boss, 2));
            goto redoTurn;
        case 5:
            screenManager.ShowPopup(player->useItem(boss, 3));
            goto redoTurn;
        case 6:
            screenManager.ShowPopup(player->useItem(boss, 4));
            goto redoTurn;
        case 7:
            screenManager.ShowPopup(player->useItem(boss, 5));
            goto redoTurn;
        default:
            cerr << "Player turn input error" << endl;
            exit(1);
    }
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
    screenManager.ShowPopup(printThis);
}

void Game::saveGame() {
    std::ofstream oFile(gameFile);
    if (!oFile.good()) {
        cerr << "Error with file ostream saveGame" << endl;
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

void Game::resetSave() {
    std::ofstream oFile(gameFile);
    if (!oFile.good()) {
        cerr << "Error with file ostream reset game save" << endl;
        exit(1);
    }

    oFile << "0\n0\n";
    oFile << playerFile << '\n';
    oFile << playerItemsFile << '\n';
    oFile << shopFile << '\n';

    shop->resetShopSave();
    player->resetPlayerSave();

    resetGame();
}

string Game::checkBuyItem(int index) {
    int cost = shop->getItemPrice(index);
    if (cost == -1) return "You have already purchased this item.";
    if (cost > calories) return "You cannot buy this. You are missing " + std::to_string(shop->getItemPrice(0)-calories) + " calories.";
    calories -= cost;
    return shop->purchaseItem(player, index);
}