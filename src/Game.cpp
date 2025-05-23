#include "Game.h"
#include <fstream>
#include <iostream>
#include <string>

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
}

int Game::gameLoop() {
    while (savePoint < 100) {
        switch (savePoint) {
            case 1:
            case 2:
            default:
                return -1;
        }
        savePoint++;
    }
    return 1;
}

int Game::battleLoop() {
    while (1) {

    }
}

int Game::playerTurn() {

}

int Game::enemyTurn() {

}

void turnReset();
int Game::deathCheck() {
    
}
void loadShop();
void saveGame();