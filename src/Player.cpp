#include "Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using std::string;
using std::cerr;

Player::Player(string file) : Fruit(file) {}

int Player::specialAttack(Fruit* target) {
    return -1;
}

void Player::levelUp() {
    level++;
    hp += 100;
    baseMaxHp += 100;
    maxHpTotal += 100;
    baseAttack += 50;
    attackTotal += 50;
    baseDefense += 25;
    defenseTotal += 25;
    baseArts += 50;
    ArtsTotal += 50;
    baseRes += 25;
    ResTotal += 25;
    baseCritRate += 10;
    critRateTotal += 10;
    baseCritDmg += 20;
    critDmgTotal += 20;
}

bool Player::useItem(Fruit* target, int itemIndex) {
    return 1;
}

int Player::endOfTurn() {
    return 1;
}

void Player::savePlayer() {
    std::ofstream oFile(fileName);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << std::endl;
        exit(1);
    }

    oFile << name << '\n';
    oFile << level << '\n';
    oFile << hp << '\n';
    oFile << baseMaxHp << '\n';
    oFile << baseAttack << '\n';
    oFile << baseDefense << '\n';
    oFile << baseArts << '\n';
    oFile << baseRes << '\n';
    oFile << baseCritRate << '\n';
    oFile << baseCritDmg;
}