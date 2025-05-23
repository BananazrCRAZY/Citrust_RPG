#include "Game.h"
#include "Boss.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cerr;
using std::string;
using std::ifstream;

Game::Game(string file) : gameFile(file) {
    ifstream iFile(gameFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream\n";
        exit(1);
    }

    iFile >> savePoint;
    iFile >> calories;
    string outFile = "";
    iFile >> outFile;
    player = new Player(outFile);
    iFile >> outFile;
    //shop = new Shop(outFile);
    iFile >> bossList;
}

int Game::gameLoop() {
    while (savePoint < 100) {
        switch (savePoint) {
            case 1:
            case 2:
                // when creating a boss use getBossFile() to get the path
            default:
                return -1;
        }
        savePoint++;
    }
    return 1;
}

string Game::getBossFile() {
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

int Game::battleLoop(Boss* boss) {

    while (1) {
        if (player->getTurn() > 0) {
            playerTurn(boss);
        }
        if (boss->getTurn() > 0) {
            enemyTurn();
        }
    }
}

int Game::playerTurn(Boss* boss) {
    // loops until input
    int input = 0;
    while (1) {
        if (input == 0) player->basicAttack(boss);
        if (input == 1) player->specialAttack(boss);
        // use item requires another input
    }
}

int Game::enemyTurn() {

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
        cerr << "Error with file ostream" << std::endl;
        exit(1);
    }

    oFile << savePoint << '\n';
    oFile << calories << "              \n";
}