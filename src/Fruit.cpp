#include "Fruit.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using std::cerr;

Fruit::Fruit(string file) : 
    fileName(file), 
    maxHpAdd(0), 
    attackAdd(0),
    defenseAdd(0),
    citrusArtsAdd(0),
    citrusResAdd(0),
    critRateAdd(0),
    critDmgAdd(0),
    rechargeCount(2),
    turn(1)
    {
        std::ifstream iFile(fileName);
        if (!iFile.good()) {
            cerr << "Error with file fstream" << std::endl;
            exit(1);
        }

        getline(iFile, name);
        iFile >> level;
        iFile >> hp;
        iFile >> baseMaxHp;
        maxHpTotal = baseMaxHp;
        iFile >> baseAttack;
        attackTotal = baseAttack;
        iFile >> baseDefense;
        defenseTotal = baseDefense;
        iFile >> baseCitrusArts;
        citrusArtsTotal = baseCitrusArts;
        iFile >> baseCitrusRes;
        citrusResTotal = baseCitrusRes;
        iFile >> baseCritRate;
        critRateTotal = baseCritRate;
        iFile >> baseCritDmg;
        critDmgTotal = baseCritDmg;
    }

int Fruit::basicAttack(Fruit* target) {
    int damage = target->getDefense() - attackTotal;
    if (damage >= 0) return 0;
    target->setHp(damage);
    return -1 * damage;
}

void Fruit::setMaxHpAdd(int change) {
    maxHpAdd += change;
    maxHpTotal += change;
}

void Fruit::setAttackAdd(int change) {
    attackAdd += change;
    attackTotal += change;
}

void Fruit::setDefenseAdd(int change) {
    defenseAdd += change;
    defenseTotal += change;
}

void Fruit::setCitrusArtsAdd(int change) {
    citrusArtsAdd += change;
    citrusArtsTotal += change;
}

void Fruit::setCitrusResAdd(int change) {
    citrusResAdd += change;
    citrusResTotal += change;
}

void Fruit::setCritRateAdd(int change) {
    critRateAdd += change;
    critRateTotal += change;
}

void Fruit::setCritDmgAdd(double change) {
    critDmgAdd += change;
    critDmgTotal += change;
}

void Fruit::endOfTurn() {
    // for (int i = 0; i < effects.size(); i++) {

    // }
    rechargeCount++;
}
