#include "Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using std::string;
using std::cerr;

Player::Player(string file) : Fruit(file) {}

int Player::specialAttack(Fruit* target) {
    
}

bool Player::useItem(Fruit* target, int itemIndex) {

}

void Player::endOfTurn() {

}

void Player::savePlayer() {
    std::ofstream oFile(fileName);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << std::endl;
        exit(1);
    }

    oFile << '\n';
    oFile << level << '\n';
    oFile << hp << '\n';
    oFile << baseMaxHp << '\n';
    oFile << baseAttack << '\n';
    oFile << baseDefense << '\n';
    oFile << baseCitrusArts << '\n';
    oFile << baseCitrusRes << '\n';
    oFile << baseCritRate << '\n';
    oFile << baseCritDmg;
}