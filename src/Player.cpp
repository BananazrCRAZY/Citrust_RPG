#include "include/json.hpp"
#include "include/Objects/Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using json = nlohmann::json;
using std::string;
using std::cerr;

Player::Player(const string& file, const string& itemFile, Shop* shop, BossItemManager& bossItemMgr) : Fruit(file),  equippedEnd(nullptr), inventoryList(itemFile) {
    std::ifstream iFile(itemFile);
    if(!iFile.good()) {
        cerr << "Error: Player.cpp, Player(), iFile opening itemFile\n";
        exit(1);
    }
    
    bool isEquipped = true;
    int output;
    while (iFile >> output) {
        if (output == -1) {
            isEquipped = false;
            continue;
        }

        if (output > 100) {
            if (isEquipped) battleItems.push_back(bossItemMgr.getBossItem(output-101));
            else items.push_back(bossItemMgr.getBossItem(output-101));
        } else {
            if (isEquipped) battleItems.push_back(shop->getItemById(output));
            else items.push_back(shop->getItemById(output));
        }
    }

    iFile.close();
}

Player::~Player() {
    effects.clear();
    for (unsigned i = 0; i < battleItems.size(); i++) delete battleItems.at(i);
    battleItems.clear();
    for (unsigned i = 0; i < items.size(); i++) delete items.at(i);
    items.clear();
    delete equippedEnd;
}

// Deals Physical DMG and Arts DMG equal to ATK and Arts ATK respectively.
// Damage dealt is counted as once instance of damage. 
// Each type of damage has its own chance to crit.
string Player::specialAttack(Fruit* target) {
    rechargeCount -= 2;
    if (!checkIfHit(target)) return name + ": Missed!";
    string returnThis = calcDamage(target, true, false) + '\n';
    return returnThis + calcDamage(target, false, false);
}

void Player::levelUp() {
    // Remove added stats and then re-add them because of percent-based items
    clearStats();
    level++;
    stats.at(0)->addBase(275);
    stats.at(1)->addBase(140);
    stats.at(2)->addBase(60);
    stats.at(3)->addBase(130);
    reAddStats();
}

void Player::endOfBattle() {
    rechargeCount = 2;
    turn = 1;
    clearStats();
    reAddStats();
    for (unsigned i = 0; i < battleItems.size(); i++) {
        if (battleItems.at(i)->isConsumableTrue()) battleItems.at(i)->resetCooldown();
    }
    hp = getStat(0);
}

void Player::endOfTurn() {
    Fruit::endOfTurn();
    for (unsigned i = 0; i < battleItems.size(); i++) {
        if (battleItems.at(i)->isConsumableTrue()) {
            if (battleItems.at(i)->getCooldown() > 0) battleItems.at(i)->decreaseCooldown();
        }
    }
}

// boss may not be used, would've had selector to use on player or boss
// however not enough time
string Player::useItem(Fruit* boss, unsigned itemIndex) {
    if (itemIndex > (battleItems.size()-1)) {
        cerr << "Error useItem index problem" << std::endl;
        exit(1);
    }
    if (!battleItems.at(itemIndex)->isConsumableTrue()) return "This is Not a Consumable.";
    if (battleItems.at(itemIndex)->getCooldown() > 0) return "Item is on Cooldown.";
    if (rechargeCount <= 0) return "Not enough Skill Points.";
    rechargeCount--;
    if (battleItems.at(itemIndex)->isUseOnPlayer()) {
        battleItems.at(itemIndex)->use(this);
        return name + " used " + battleItems.at(itemIndex)->getName() + " on " + name + ".";
    }
    battleItems.at(itemIndex)->use(boss);
    return name + " used " + battleItems.at(itemIndex)->getName() + " on " + boss->getName() + ".";
}

void Player::savePlayer() {
    std::ofstream oFile(fileName, std::ios::trunc);
    if (!oFile.good()) {
        cerr << "Error with saving Fruit file ostream" << std::endl;
        exit(1);
    }

    oFile << name << '\n';
    oFile << level << '\n';
    oFile << hp << '\n';
    oFile << stats.at(0)->getBase() << '\n';
    oFile << stats.at(1)->getBase() << '\n';
    oFile << stats.at(2)->getBase() << '\n';
    oFile << stats.at(3)->getBase() << '\n';
    oFile << "10\n10\n50\n0\n95\n0\n0\n0\n0\n0";
    oFile.close();

    oFile.open(inventoryList);
    if (!oFile.good()) {
        cerr << "Error: Player.cpp, savePlayer(), inventoryList open !good\n";
        exit(1);
    }

    for (Item* item : battleItems) oFile << item->getId() << '\n';
    oFile << "-1\n";
    for (Item* item : items) oFile << item->getId() << '\n';

    oFile.close();
}

void Player::resetPlayerSave() {
    // Player
    std::ofstream oFile(fileName, std::ios::trunc);
    if (!oFile.good()) {
        cerr << "Error with reseting player file ostream" << std::endl;
        exit(1);
    }

    oFile << "null name" << '\n';  // name
    oFile << 1 << '\n';  // level
    oFile << 200 << '\n';  // max hp
    oFile << 200 << '\n';  // hp
    oFile << 150 << '\n';  // atk
    oFile << 75 << '\n';  // def
    oFile << 100 << '\n';  // arts
    oFile << 10 << '\n';  // res
    oFile << 10 << '\n';  // crit rate
    oFile << 50 << '\n';  // crit dmg
    oFile << "0\n95\n0\n0\n0\n0\n0";
    oFile.close();

    // inventory
    oFile.open(inventoryList, std::ios::trunc);
    if (!oFile.good()) {
        cerr << "Error: Player.cpp, resetPlayerSave(), opening inventoryList\n";
        exit(1);
    }
    
    oFile << "-1\n";

    oFile.close();
}

void Player::unequipItem(unsigned index) {
    if (index > (battleItems.size()-1)) {
        cerr << "Error removeItem index problem" << std::endl;
        exit(1);
    }
    if (!battleItems.at(index)->isConsumableTrue()) {
        removeEffect(battleItems.at(index)->getStatus());
        rechargeCount += -1 * battleItems.at(index)->getStatus()->getRechargeCountChange();
    }
    items.push_back(battleItems.at(index));
    battleItems.erase(battleItems.begin() + index);
    hp = getStat(0);
}

void Player::equipItem(unsigned index) {
    if (index > (items.size()-1)) {
        cerr << "Error addItem index problem" << std::endl;
        exit(1);
    }
    if (!items.at(index)->isConsumableTrue()) addEffect(items.at(index)->getStatus());
    battleItems.push_back(items.at(index));
    items.erase(items.begin() + index);
    hp = getStat(0);
}

void Player::clearStats() {
    effects.clear();
    for (Stat* stat : stats) stat->removeAdd();
    if (hp > getStat(0)) hp = getStat(0);
}

void Player::reAddStats() {
    for (unsigned i = 0; i < battleItems.size(); i++) {
        if (!battleItems.at(i)->isConsumableTrue()) {
            effects.push_back(battleItems.at(i)->getStatus());
            addStats(effects.at(effects.size()-1));
        }
    }
}