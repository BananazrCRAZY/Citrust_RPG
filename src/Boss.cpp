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
    int cost, cooldownDefault, appearanceProb, isConsumable, uses;
    getline(iFile, itemName);
    getline(iFile, itemDesc);
    iFile >> cost;
    iFile >> isConsumable;
    iFile >> uses;
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

    Status* stat = new Status(statusName, statusDesc, defaultTurns, percentBased, hpChange, maxHpChange, attackChange, defenseChange, artsChange, resChange, critRateChange, critDamageChange, rechargeCountChange, turnChange);
    itemDrop = new Item(itemName, itemDesc, cost, uses, cooldownDefault, stat, appearanceProb, isConsumable);
}

int Boss::endOfTurn() {

}