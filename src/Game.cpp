#include "Game.h"
#include "Boss.h"
#include "Apple.h"
#include "Pear.h"
#include "Strawberry.h"
#include "Grape.h"
#include "Dekopon.h"
#include "MangoGreen.h"
#include "MangoRed.h"
#include "Pineapple.h"
#include "Durian.h"
#include "Watermelon.h"
#include "Shop.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cerr;
using std::string;
using std::ifstream;
using std::endl;

void Game::runGame() {
    startGame();
    if (savePoint == 0) {  // get ui to send name
        string inputName;
        player->setName(inputName);
    }
    gameLoop();
    loadEndOfGame();
}

void Game::resetGame() {
    delete player;
    delete shop;
}

void Game::openFile(string file) {
    gameFile = file;
    ifstream iFile(gameFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    iFile >> savePoint;
    iFile >> calories;
    iFile >> playerFile;
    iFile >> playerItemsFile;
    player = new Player(playerFile, playerItemsFile);
    iFile >> shopFile;
    shop = new Shop(shopFile);
    iFile >> bossList;
    iFile >> dialogueList;
}

void Game::startGame() {
    // need ui input
    int input;
    switch (input) {    
        case 0:
            exit(0);
        case 1:
            // new game
            openFile("assets/saves/Save1/Game.txt");
            break;
        case 2:
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
        // need ui to show screen based on savePoint
        Boss* boss;
        switch (savePoint) {
            case 0:
                // create boss here, use getBossFile and hard code item and required charge
                boss = new Apple();
                break;
            case 1:
                boss = new Pear();
                break;
            case 2:
                boss = new Strawberry();
                break;
            case 3:
                boss = new Grape();
                break;
            case 4:
                boss = new Dekopon();
                break;
            case 5:
                boss = new MangoGreen();
                break;
            case 6:
                boss = new Pineapple();
                break;
            case 7:
                boss = new Durian();
                break;
            case 8:
                boss = new Watermelon();
                break;
            default:
                cerr << "Game loop input error" << endl;
                exit(1);
        }
        // battleResult: -1 is a loss, if positive then it's the number of cycles
        int battleResult = battleLoop(boss);
        if (savePoint == 5) {
            delete boss;
            boss = new MangoRed();
            battleResult += battleLoop(boss);
        }
        player->newItem(boss->getItem());
        delete boss;
        if (battleResult == -1) loadLose();
        int addCalories = player->getLevel() * 1000 / battleResult;
        if (addCalories < 75) addCalories = 75;
        calories += addCalories;

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

void Game::loadEndOfGame() {
    resetGame();
    // have the ui end game screen here and get input
    int input;
    switch(input) {
        case 0:
            exit(1);
        case 1:
            startGame();
            break;
        default:
    }
}

void Game::loadLose() {
    resetGame();
    // have ui load lose screen and get input
    int input;
    switch(input) {
        case 0:
            exit(1);
        case 1:
            startGame();
            break;
        default:
    }
}

string Game::getBossFile() const {
    ifstream iFile(bossList);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    string bossFile = "";
    int counter = savePoint;
    while (counter != 0) {
        iFile >> bossFile;
        counter--;
    }
    return bossFile;
}

// string Game::getDialogueFile() const {
//     ifstream iFile(dialogueList);
//     if (!iFile.good()) {
//         cerr << "Error with file fstream\n";
//         exit(1);
//     }

//     string dialogueFile = "";
//     int counter = savePoint;
//     while (counter >= 0) {
//         iFile >> dialogueFile;
//         counter--;
//     }
//     return dialogueFile;
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
            print = player->useItem(player, 0);
            break;
        case 3:
            print = player->useItem(player, 1);
            break;
        case 4:
            print = player->useItem(player, 2);
            break;
        case 5:
            print = player->useItem(player, 3);
            break;
        case 6:
            print = player->useItem(player, 4);
            break;
        case 7:
            print = player->useItem(player, 5);
            break;
        case 8:
            print = player->useItem(boss, 0);
            break;
        case 9:
            print = player->useItem(boss, 1);
            break;
        case 10:
            print = player->useItem(boss, 2);
            break;
        case 11:
            print = player->useItem(boss, 3);
            break;
        case 12:
            print = player->useItem(boss, 4);
            break;
        case 13:
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
    oFile << bossList << '\n';
    oFile << dialogueList << '\n';

    shop->saveShop();
    player->savePlayer();
}

string Game::checkBuyItem(int index) {
    if (shop->getItemPrice(index) > calories) return "You cannot buy this. You are missing " + std::to_string(shop->getItemPrice(0)-calories) + " calories.";
    return shop->purchaseItem(player, index);
}