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
        if (unequipped) items.push_back(item);
        else battleItems.push_back(item);
    }
    iFile.close();
}

int Player::specialAttack(Fruit* target) {
    return -1;
}

void Player::levelUp() {
    // removing then adding again bc %based items
    for (int i = 0; i < battleItems.size(); i++) removeStats(battleItems.at(i)->getStatus());
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
    for (int i = 0; i < battleItems.size(); i++) addStats(battleItems.at(i)->getStatus());
}

bool Player::useItem(Fruit* target, unsigned itemIndex) {
    if (itemIndex > (battleItems.size()-1)) {
        cerr << "Error useItem index problem" << std::endl;
        exit(1);
    }
    battleItems.at(itemIndex)->use(target);
    cycleThroughEffects();
}

// goes through effects and add to recharge, does not check dead
int Player::endOfTurn() {
    for (int i = 0; i < effects.size(); i++) {
        if (effects.at(i)->getTurns() == 0) {
            removeStats(effects.at(i));
            effects.at(i)->resetStatus();
            effects.erase(effects.begin()+i);
        }
        effects.at(i)->decreaseTurn();
    }
    rechargeCount++;
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

void Player::removeItem(unsigned index) {
    if (index > (battleItems.size()-1)) {
        cerr << "Error removeItem index problem" << std::endl;
        exit(1);
    }
    removeStats(battleItems.at(index)->getStatus());
    items.push_back(battleItems.at(index));
    battleItems.erase(battleItems.begin() + index);
}

void Player::addItem(unsigned index) {
    if (index > (items.size()-1)) {
        cerr << "Error addItem index problem" << std::endl;
        exit(1);
    }
    addStats(items.at(index)->getStatus());
    battleItems.push_back(items.at(index));
    items.erase(items.begin() + index);
}