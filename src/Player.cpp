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

string Player::specialAttack(Fruit* target) {
    // sebastian implement this
    return "-1";
}

void Player::levelUp() {
    // removing then adding again bc %based items
    clearStats();
    level++;
    // add to base stats here
}

bool Player::useItem(Fruit* target, unsigned itemIndex) {
    if (itemIndex > (battleItems.size()-1)) {
        cerr << "Error useItem index problem" << std::endl;
        exit(1);
    }
    battleItems.at(itemIndex)->use(target);
}

void Player::savePlayer() {
    std::ofstream oFile(fileName);
    if (!oFile.good()) {
        cerr << "Error with file ostream" << std::endl;
        exit(1);
    }

    // need to fix if there is overflow
    oFile << name << '\n';
    oFile << level << '\n';
    oFile << hp << '\n';
    oFile << maxHp->getBase() << '\n';
    oFile << attack->getBase() << '\n';
    oFile << defense->getBase() << '\n';
    oFile << arts->getBase() << '\n';
    oFile << res->getBase() << '\n';
    oFile << critRate->getBase() << '\n';
    oFile << critDmg->getBase();
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