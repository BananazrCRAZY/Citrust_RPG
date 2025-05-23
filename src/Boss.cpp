#include "Boss.h"
#include "Item.h"
#include "Status.h"
#include <string>
#include <fstream>
#include <iostream>

using std::cerr;
using std::string;
using std::ifstream;

Boss::Boss(string mainFile, string itemF) : Fruit(mainFile), itemFile(itemF) {
    ifstream iFile(itemFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream" << std::endl;
        exit(1);
    }

    string itemName, itemDesc, statusFile;
    int cost, cooldownDefault, appearanceProb, isConsumable;
    getline(iFile, itemName);
    getline(iFile, itemDesc);
    iFile >> cost;
    iFile >> isConsumable;
    iFile >> cooldownDefault;
    iFile >> appearanceProb;
    iFile >> statusFile;
    iFile.close();
    
    iFile.open(statusFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream" << std::endl;
        exit(1);
    }

    string statusName, statusDesc;
    int defaultTurns, percentBased, hpChange, maxHpChange, attackChange, defenseChange, artsChange, resChange, critRateChange, critDamageChange, rechargeCountChange, turnChange;
    getline(iFile, statusName);
    getline(iFile, statusDesc);
    iFile >> defaultTurns;
    iFile >> percentBased;
    iFile >> hpChange;
    iFile >> maxHpChange;
    iFile >> attackChange;
    iFile >> defenseChange;
    iFile >> artsChange;
    iFile >> resChange;
    iFile >> critRateChange;
    iFile >> critDamageChange;
    iFile >> rechargeCountChange;
    iFile >> turnChange;
    iFile.close();

    Status* stat = new Status(statusName, statusDesc, defaultTurns, percentBased, hpChange, maxHpChange, attackChange, defenseChange, artsChange, resChange, critRateChange, critDamageChange, rechargeCountChange, turnChange, false);
    itemDrop = new Item(itemName, itemDesc, cost, cooldownDefault, stat, appearanceProb, isConsumable);
}

int Boss::specialAttack(Fruit* target) {
    int damage = attackTotal * 2;
    if (checkIfCrit()) damage = damage * (critDmgTotal/100 + 1);
    damage  = damage - target->getDefense();
    if (damage <= 0) return 0;
    target->setHp(-1*damage);
    return damage;
}

int Boss::endOfTurn() {

}