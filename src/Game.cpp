#include "Game.h"
#include "Boss.h"
#include "UI.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

using std::cerr;
using std::string;
using std::ifstream;

void Game::openFile(string file) {
    gameFile = file;
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
    iFile >> dialogueList;
}

void Game::startGame() {
    int input = ui.startMenu();
    switch (input) {
        case 0:
            exit(0);
        case 1:
        case 2:
            openFile("assets/saves/Save1/Game.txt");
        case 3:
            openFile("assets/saves/Save2/Game.txt");
        case 4:
            openFile("assets/saves/Save2/Game.txt");
        default:
            exit(0);
    }
    gameLoop();
}

int Game::gameLoop() {
    while (savePoint < 100) {
        switch (savePoint) {
            case 0:
                ui.printDialogue(getDialogueFile());
            case 1:
                ui.printDialogue(getDialogueFile());
                // create pear boss here
            case 2:
                ui.printDialogue(getDialogueFile());
                // when creating a boss use getBossFile() to get the path
                // apple here
            default:
                return -1;
        }
        savePoint++;
        saveGame();
    }
    return 1;
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