#include "Game.h"
#include "Boss.h"
#include "Apple.h"
#include "UI.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cerr;
using std::string;
using std::ifstream;
using std::endl;

void Game::openFile(string file) {
    gameFile = file;
    ifstream iFile(gameFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    iFile >> savePoint;
    iFile >> calories;
    string playerFile, playerItemsFile, shopFile;
    iFile >> playerFile;
    iFile >> playerItemsFile;
    player = new Player(playerFile, playerItemsFile);
    iFile >> shopFile;
    //shop = new Shop(shopFile);
    iFile >> bossList;
    iFile >> dialogueList;
}

void Game::startGame() {
    int input = ui.startMenu();
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

int Game::gameLoop() {
    while (savePoint < 10) {
        ui.printDialogue(getDialogueFile());
        if (savePoint != 0) {
            Boss* boss;
            switch (savePoint) {
                case 1:
                    // create boss here, use getBossFile and hard code item
                    break;
                case 2:
                    break;
                default:
                    cerr << "Game loop input error" << endl;
                    exit(1);
            }
            // put boss into battle loop
            battleLoop(boss);
        }
        loadShop();
        savePoint++;
    }
    return 1;
}

void Game::loadShop() {
    int input;
    while (input != 0) {

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

string Game::getDialogueFile() const {
    ifstream iFile(dialogueList);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    string dialogueFile = "";
    int counter = savePoint;
    while (counter >= 0) {
        iFile >> dialogueFile;
        counter--;
    }
    return dialogueFile;
}

int Game::battleLoop(Boss* boss) {
    bool battling = true;
    while (battling) {
        if (player->getTurn() > 0) {
            playerTurn(boss);
        }
        if (boss->getTurn() > 0) {
            enemyTurn(boss);
        }
    }
}

int Game::playerTurn(Boss* boss) {
    int input = ui.playerAction(player);
    switch (input) {
        case 0:
            player->basicAttack(boss);
        case 1:
            player->specialAttack(boss);
        case 2:
            player->useItem(player, 0);
        case 3:
            player->useItem(player, 1);
        case 4:
            player->useItem(player, 2);
        case 5:
            player->useItem(player, 3);
        case 6:
            player->useItem(player, 4);
        case 7:
            player->useItem(player, 5);
        case 8:
            player->useItem(boss, 0);
        case 9:
            player->useItem(boss, 1);
        case 10:
            player->useItem(boss, 2);
        case 11:
            player->useItem(boss, 3);
        case 12:
            player->useItem(boss, 4);
        case 13:
            player->useItem(boss, 5);
        default:
            cerr << "Player turn input error" << endl;
            exit(1);
    }
}

int Game::enemyTurn(Boss* boss) {
    if (boss->getBossAttackCharge() == ) {

    }
}

void Game::turnReset() {

}

int Game::deathCheck() {

}

void Game::loadShop() {

}
void Game::saveGame() {
    std::ofstream oFile(gameFile);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << endl;
        exit(1);
    }

    oFile << savePoint << '\n';
    oFile << calories << "              \n";
}