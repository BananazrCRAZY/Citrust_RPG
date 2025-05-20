#include "Fruit.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using std::cerr;

Fruit::Fruit(string file) : fileName(file) {
    std::ifstream iFile(fileName);
    if (!iFile.good()) {
        cerr << "Error with file fstream" << std::endl;
        exit(1);
    }

    getline(iFile, name);
    iFile >> level;
    iFile >> hp;
    iFile >> baseMaxHp;
    iFile >> baseAttack;
    iFile >> baseDefense;
    iFile >> baseCitrusArts;
    iFile >> baseCitrusRes;
    iFile >> baseCritRate;
    iFile >> baseCritDmg;
}

int Fruit::basicAttack(Fruit* target) {
    int damage = target->getDefense() - attackTotal;
    if (damage > 0) return 0;
    target->setHp(damage);
    return -1 * damage;
}

void Fruit::setMaxHpAdd(int change) {
    maxHpAdd += change;
    maxHpTotal += change;
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
