#include "Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using std::string;
using std::cerr;

Player::Player(string file, string itemFile) : Fruit(file),  inventoryList(itemFile) {
    std::ifstream iFile(itemFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream" << std::endl;
        exit(1);
    }

    string output = "";
    bool unequipped = false;
    Item* item;
    while(iFile >> output) {
        if (output == "unequipped") {
            unequipped = true;
            continue;
        }

        item = new Item(output);
        if (unequipped) {

        } else {

        }
    }
}

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
    battleItems.at(itemIndex)->use(target);
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
    oFile.close();

    oFile.open(inventoryList);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << std::endl;
        exit(1);
    }

    for (int i = 0; i < battleItems.size(); i++) {
        oFile << battleItems.at(i)->getFile() << '\n';
    }
    oFile << 'unequipped\n';
    for (int i = 0; i < items.size(); i++) {
        oFile << items.at(i)->getFile() << '\n';
    }
    oFile.close();
}

void Player::removeItem(int index) {
    items.push_back(battleItems.at(index));
    battleItems.erase(battleItems.begin() + index);
}

void Player::addItem(int index) {
    battleItems.push_back(items.at(index));
    items.erase(items.begin() + index);
}