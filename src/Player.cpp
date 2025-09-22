#include "include/json.hpp"
#include "include/Objects/Player.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using json = nlohmann::json;
using std::string;
using std::cerr;

Player::Player(const string& file, const string& itemFile) : Fruit(file),  equippedEnd(nullptr), inventoryList(itemFile) {
    std::ifstream iFile(itemFile);
    if(!iFile.good()) {
        cerr << "Error: Player.cpp, Player(), iFile not good";
        exit(1);
    }
    json data;
    iFile >> data;

    bool equipped = true;
    for (auto& it : data) {
        int id = it.value("id", -1);
        if (id == 0) {
            equipped = false;
            equippedEnd = new Item(0, "equipped", "", 0, false, 0, 0, false, "");
            continue;
        }
        string name = it.value("name", "Error name");

        string desc = it.value("description", "");
        int cost = it.value("cost", 0);
        bool consumable = it.value("consumable", 0) != 0;
        int cooldownDefault = it.value("cooldownDefault", 0);
        int appearanceProb = it.value("appearanceProbability", 0);
        bool useOnPlayer = it.value("useOnPlayer", 0) != 0;
        string iconPath = it.value("iconPath", "");

        if (equipped) battleItems.push_back(new Item(
                id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath
            ));
        else items.push_back(new Item(
                id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath
            ));
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

    oFile.open(inventoryList);
    if (!oFile.good()) {
        cerr << "Error: Player.cpp, savePlayer(), inventoryList open !good\n";
        exit(1);
    }

    json data = json::array();

    for (Item* item : battleItems) {
        json obj;
        obj["id"] = item->getId();
        obj["name"] = item->getName();
        obj["description"] = item->getDescription();
        obj["cost"] = item->getCost();
        obj["consumable"] = item->isConsumableTrue() ? 1 : 0;
        obj["cooldownDefault"] = item->getCooldownDefault();
        obj["appearanceProbability"] = item->getAppearanceProbabiity();
        obj["useOnPlayer"] = item->isUseOnPlayer() ? 1 : 0;
        obj["iconPath"] = item->getIcon();

        data.push_back(obj);
    }

    if (equippedEnd != nullptr) {
        json endMarker;
        endMarker["id"] = equippedEnd->getId();
        endMarker["name"] = equippedEnd->getName();
        data.push_back(endMarker);
    }

    for (Item* item : items) {
        json obj;
        obj["id"] = item->getId();
        obj["name"] = item->getName();
        obj["description"] = item->getDescription();
        obj["cost"] = item->getCost();
        obj["consumable"] = item->isConsumableTrue() ? 1 : 0;
        obj["cooldownDefault"] = item->getCooldownDefault();
        obj["appearanceProbability"] = item->getAppearanceProbabiity();
        obj["useOnPlayer"] = item->isUseOnPlayer() ? 1 : 0;
        obj["iconPath"] = item->getIcon();

        data.push_back(obj);
    }

    oFile << data.dump(2);
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
    if (!battleItems.at(index)->isConsumableTrue()) {
        removeEffect(battleItems.at(index)->getStatus());
        rechargeCount += -1 * battleItems.at(index)->getStatus()->getRechargeCountChange();
    }
    items.push_back(battleItems.at(index));
    battleItems.erase(battleItems.begin() + index);
    hp = maxHp->getTotal();
}

void Player::equipItem(unsigned index) {
    if (index > (items.size()-1)) {
        cerr << "Error addItem index problem" << std::endl;
        exit(1);
    }
    if (!items.at(index)->isConsumableTrue()) addEffect(items.at(index)->getStatus());
    battleItems.push_back(items.at(index));
    items.erase(items.begin() + index);
    hp = maxHp->getTotal();
}

void Player::clearStats() {
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