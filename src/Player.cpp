#include "include/Objects/Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using std::string;
using std::cerr;

Player::Player(const string& file, const string& itemFile) : Fruit(file),  inventoryList(itemFile) {
    std::ifstream iFile(itemFile);
    if (!iFile.good()) {
        cerr << "Error with Inventory list file fstream" << std::endl;
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
        else {
            battleItems.push_back(item);
            if (!battleItems.at(battleItems.size()-1)->isConsumableTrue()) 
                addEffect(battleItems.at(battleItems.size()-1)->getStatus());
        }
    }
    iFile.close();
}

Player::~Player() {
    clearEffectsVector();
    effects.clear();
    for (unsigned i = 0; i < battleItems.size(); i++) delete battleItems.at(i);
    battleItems.clear();
    for (unsigned i = 0; i < items.size(); i++) delete items.at(i);
    items.clear();
}

// Deals Physical DMG and Arts DMG equal to ATK and Arts ATK respectively. Damage dealt is counted as once instance of damage. However, each type of damage has its own chance to crit.
string Player::specialAttack(Fruit* target) {
    string returnThis = "";
    int physDmg = attack->getTotal();
    int artsDmg = arts->getTotal();
    if (checkIfCrit()) {
        physDmg *= (critDmg->getTotal()/100.0 + 1);
        artsDmg *= (critDmg->getTotal()/100.0 + 1);
        returnThis += "CRIT!\n";
    }
    physDmg -= target->getDefense();
    if (physDmg <= 0) physDmg = 0;
    artsDmg *= (1.0 - (target->getRes()/100.0));
    if (artsDmg <= 0) artsDmg = 0;
    int damageDealt = physDmg + artsDmg;
    if (damageDealt <= 0) return returnThis + name + ": Dealt 0 damage.";
    target->setHp(-1 * damageDealt);

    rechargeCount -= 2;
    return returnThis + name + ": Dealt " + std::to_string(damageDealt) + " damage.";
}

void Player::levelUp() {
    // Remove added stats and then re-add them because of percent-based items
    clearStats();
    level++;
    maxHp->addBase(275);
    attack->addBase(140);
    defense->addBase(60);
    arts->addBase(130);
    reAddStats();
}

void Player::endOfBattle() {
    hp = maxHp->getTotal();
    rechargeCount = 2;
    turn = 1;
    clearStats();
    reAddStats();
    for (unsigned i = 0; i < battleItems.size(); i++) {
        if (battleItems.at(i)->isConsumableTrue()) battleItems.at(i)->resetCooldown();
    }
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
    oFile << maxHp->getBase() << '\n';
    oFile << attack->getBase() << '\n';
    oFile << defense->getBase() << '\n';
    oFile << arts->getBase() << '\n';
    oFile << res->getBase() << '\n';
    oFile << critRate->getBase() << '\n';
    oFile << critDmg->getBase() << '\n';
    oFile.close();

    oFile.open(inventoryList, std::ios::trunc);
    if (!oFile.good()) {
        cerr << "Error with saving Inventory list file ostream" << std::endl;
        exit(1);
    }

    for (int i = 0; i < battleItems.size(); i++) {
        oFile << battleItems.at(i)->getFilePath() << '\n';
    }
    oFile << "unequipped\n";
    for (int i = 0; i < items.size(); i++) {
        oFile << items.at(i)->getFilePath() << '\n';
    }
    oFile.close();
}

void Player::resetPlayerSave() {
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
    oFile.close();

    oFile.open(inventoryList, std::ios::trunc);
    if (!oFile.good()) {
        cerr << "Error with reset Inventory list file ostream" << std::endl;
        exit(1);
    }
    oFile << "unequipped\n";
    oFile.close();
}

void Player::unequipItem(unsigned index) {
    if (index > (battleItems.size()-1)) {
        cerr << "Error removeItem index problem" << std::endl;
        exit(1);
    }
    if (!battleItems.at(index)->isConsumableTrue()) removeEffect(battleItems.at(index)->getStatus());
    items.push_back(battleItems.at(index));
    battleItems.erase(battleItems.begin() + index);
}

void Player::equipItem(unsigned index) {
    if (index > (items.size()-1)) {
        cerr << "Error addItem index problem" << std::endl;
        exit(1);
    }
    if (!items.at(index)->isConsumableTrue()) addEffect(items.at(index)->getStatus());
    battleItems.push_back(items.at(index));
    items.erase(items.begin() + index);
}

void Player::clearStats() {
    clearEffectsVector();
    effects.clear();
    maxHp->removeAdd();
    attack->removeAdd();
    defense->removeAdd();
    arts->removeAdd();
    res->removeAdd();
    critRate->removeAdd();
    critDmg->removeAdd();
    if (hp > maxHp->getTotal()) hp = maxHp->getTotal();
}

void Player::reAddStats() {
    for (unsigned i = 0; i < battleItems.size(); i++) {
        if (!battleItems.at(i)->isConsumableTrue()) {
            effects.push_back(battleItems.at(i)->getStatus());
            addStats(effects.at(effects.size()-1));
        }
    }
}