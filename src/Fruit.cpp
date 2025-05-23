#include "Fruit.h"
#include "Status.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using std::cerr;
using std::srand;
using std::rand;
using std::time;

Fruit::Fruit(string file) : 
    fileName(file), 
    maxHpAdd(0), 
    attackAdd(0),
    defenseAdd(0),
    ArtsAdd(0),
    ResAdd(0),
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
        iFile >> baseMaxHp >> maxHpTotal;
        iFile >> baseAttack >> attackTotal;
        iFile >> baseDefense >> defenseTotal;
        iFile >> baseArts >> ArtsTotal;
        iFile >> baseRes >> ResTotal;
        iFile >> baseCritRate >> critRateTotal;
        iFile >> baseCritDmg >> critDmgTotal;
        if (!iFile.good()) {
            cerr << "Error with file fstream" << std::endl;
            exit(1);
        }
        iFile.close();
    }

int Fruit::basicAttack(Fruit* target) {
    int damage = attackTotal;
    if (checkIfCrit()) damage = damage * (critDmgTotal/100 + 1);
    damage  = damage - target->getDefense();
    if (damage <= 0) return 0;
    target->setHp(-1*damage);
    return damage;
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

void Fruit::setArtsAdd(int change) {
    ArtsAdd += change;
    ArtsTotal += change;
}

void Fruit::setResAdd(int change) {
    ResAdd += change;
    ResTotal += change;
}

void Fruit::setCritRateAdd(int change) {
    critRateAdd += change;
    critRateTotal += change;
}

void Fruit::setCritDmgAdd(double change) {
    critDmgAdd += change;
    critDmgTotal += change;
}

bool Fruit::checkIfCrit() {
    srand(time(0));
    if (((rand() % 100) + 1) > critRateTotal) return false;
    return true;
}

bool Fruit::isDead() const {
    if (hp <= 0) return true;
    return false;
}

void Fruit::removeStats(Status* status) {
    if (status->isPercentBased()) {
        maxHpTotal -= (status->getMaxHpChange() * baseMaxHp);
        maxHpAdd -= (status->getMaxHpChange() * baseMaxHp);
        attackTotal -= (status->getAttackChange() * baseAttack);
        attackAdd -= (status->getAttackChange() * baseAttack);
        defenseTotal -= (status->getDefenseChange() * baseDefense);
        defenseAdd -= (status->getDefenseChange() * baseDefense);
        ArtsTotal -= (status->getArtsChange() * baseArts);
        ArtsAdd -= (status->getArtsChange() * baseArts);
        ResTotal -= (status->getResChange() * baseRes);
        ResAdd -= (status->getResChange() * baseRes);
        critRateTotal -= (status->getCritRateChange() * baseCritRate);
        critRateAdd -= (status->getCritRateChange() * baseCritRate);
        critDmgTotal -= (status->getCritDamageChange() * baseCritDmg);
        critDmgAdd -= (status->getCritDamageChange() * baseCritDmg);
    } else {
        maxHpTotal -= status->getMaxHpChange();
        maxHpAdd -= status->getMaxHpChange();
        attackTotal -= status->getAttackChange();
        attackAdd -= status->getAttackChange();
        defenseTotal -= status->getDefenseChange();
        defenseAdd -= status->getDefenseChange();
        ArtsTotal -= status->getArtsChange();
        ArtsAdd -= status->getArtsChange();
        ResTotal -= status->getResChange();
        ResAdd -= status->getResChange();
        critRateTotal -= status->getCritRateChange();
        critRateAdd -= status->getCritRateChange();
        critDmgTotal -= status->getCritDamageChange();
        critDmgAdd -= status->getCritDamageChange();
    }
    if (hp > maxHpTotal) hp = maxHpTotal;
}

void Fruit::addStats(Status* status) {
    if (status->isPercentBased()) {
        hp += ((status->getHpChange() * maxHpTotal) + (status->getMaxHpChange() * baseMaxHp));
        maxHpTotal += (status->getMaxHpChange() * baseMaxHp);
        maxHpAdd += (status->getMaxHpChange() * baseMaxHp);
        attackTotal += (status->getAttackChange() * baseAttack);
        attackAdd += (status->getAttackChange() * baseAttack);
        defenseTotal += (status->getDefenseChange() * baseDefense);
        defenseAdd += (status->getDefenseChange() * baseDefense);
        ArtsTotal += (status->getArtsChange() * baseArts);
        ArtsAdd += (status->getArtsChange() * baseArts);
        ResTotal += (status->getResChange() * baseRes);
        ResAdd += (status->getResChange() * baseRes);
        critRateTotal += (status->getCritRateChange() * baseCritRate);
        critRateAdd += (status->getCritRateChange() * baseCritRate);
        critDmgTotal += (status->getCritDamageChange() * baseCritDmg);
        critDmgAdd += (status->getCritDamageChange() * baseCritDmg);
    } else {
        hp += (status->getHpChange() + status->getMaxHpChange());
        maxHpTotal += status->getMaxHpChange();
        maxHpAdd += status->getMaxHpChange();
        attackTotal += status->getAttackChange();
        attackAdd += status->getAttackChange();
        defenseTotal += status->getDefenseChange();
        defenseAdd += status->getDefenseChange();
        ArtsTotal += status->getArtsChange();
        ArtsAdd += status->getArtsChange();
        ResTotal += status->getResChange();
        ResAdd += status->getResChange();
        critRateTotal += status->getCritRateChange();
        critRateAdd += status->getCritRateChange();
        critDmgTotal += status->getCritDamageChange();
        critDmgAdd += status->getCritDamageChange();
        rechargeCount += status->getRechargeCountChange();
        turn += status->getTurnChange();
    }
}

void Fruit::addEffect(Status* effect) {
    effects.push_back(effect);
    cycleThroughEffects();
}

// does not decrease turn count
void Fruit::cycleThroughEffects() {
    for (int i = 0; i < effects.size(); i++) removeStats(effects.at(i));
    for (int i = 0; i < effects.size(); i++) addStats(effects.at(i));
}