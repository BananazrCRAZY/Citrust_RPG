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
        int output = 0;
        iFile >> output;
        maxHp = new Stat(output);
        iFile >> output;
        attack = new Stat(output);
        iFile >> output;
        defense = new Stat(output);
        iFile >> output;
        arts = new Stat(output);
        iFile >> output;
        res = new Stat(output);
        iFile >> output;
        critRate = new Stat(output);
        iFile >> output;
        critDmg = new Stat(output);

        if (!iFile.good()) {
            cerr << "Error with file fstream" << std::endl;
            exit(1);
        }
        iFile.close();
    }

Fruit::~Fruit() {
    delete maxHp;
    delete attack;
    delete defense;
    delete arts;
    delete res;
    delete critRate;
    delete critDmg;
}

string Fruit::basicAttack(Fruit* target) {
    int damage = attack->getTotal();
    if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
    damage = damage - target->getDefense();
    if (damage <= 0) return name + " did 0 damage.";
    target->setHp(-1*damage);
    return name + " did " + std::to_string(damage) + " damage.";
}

bool Fruit::checkIfCrit() {
    srand(time(0));
    if (((rand() % 100) + 1) > critRate->getTotal()) return false;
    return true;
}

bool Fruit::isDead() const {
    if (hp <= 0) return true;
    return false;
}

void Fruit::removeStats(Status* status) {
    if (status->isPercentBased()) {
        maxHp->add(-1 * status->getMaxHpChange() * maxHp->getBase());
        attack->add(-1 * status->getAttackChange() * attack->getBase());
        defense->add(-1 * status->getDefenseChange() * defense->getBase());
        arts->add(-1 * status->getArtsChange() * arts->getBase());
        res->add(-1 * status->getResChange() * res->getBase());
        critRate->add(-1 * status->getCritRateChange() * critRate->getBase());
        critDmg->add(-1 * status->getCritDamageChange() * critDmg->getBase());
    } else {
        maxHp->add(-1 * status->getMaxHpChange());
        attack->add(-1 * status->getAttackChange());
        defense->add(-1 * status->getDefenseChange());
        arts->add(-1 * status->getArtsChange());
        res->add(-1 * status->getResChange());
        critRate->add(-1 * status->getCritRateChange());
        critDmg->add(-1 * status->getCritDamageChange());
    }
    if (hp > maxHp->getTotal()) hp = maxHp->getTotal();
}

void Fruit::addStats(Status* status) {
    if (status->isPercentBased()) {
        maxHp->add(status->getMaxHpChange() * maxHp->getBase());
        attack->add(status->getAttackChange() * attack->getBase());
        defense->add(status->getDefenseChange() * defense->getBase());
        arts->add(status->getArtsChange() * arts->getBase());
        res->add(status->getResChange() * res->getBase());
        critRate->add(status->getCritRateChange() * critRate->getBase());
        critDmg->add(status->getCritDamageChange() * critDmg->getBase());
    } else {
        maxHp->add(status->getMaxHpChange());
        attack->add(status->getAttackChange());
        defense->add(status->getDefenseChange());
        arts->add(status->getArtsChange());
        res->add(status->getResChange());
        critRate->add(status->getCritRateChange());
        critDmg->add(status->getCritDamageChange());
    }
    if (hp > maxHp->getTotal()) hp = maxHp->getTotal();
}

void Fruit::addEffect(Status* effect) {
    effects.push_back(effect);
    addStats(effect);
}

// goes through effects and add to recharge, does not check dead
void Fruit::endOfTurn() {
    for (int i = 0; i < effects.size(); i++) {
        if (effects.at(i)->getTurns() == 0) {
            removeStats(effects.at(i));
            effects.at(i)->resetStatus();
            effects.erase(effects.begin()+i);
        }
        effects.at(i)->decreaseTurn();
    }
    rechargeCount++;
}

void Fruit::clearStats() {
    maxHp->removeAdd();
    attack->removeAdd();
    defense->removeAdd();
    arts->removeAdd();
    res->removeAdd();
    critRate->removeAdd();
    critDmg->removeAdd();
}

void Fruit::clearStatus() {
    clearStats();
    effects.clear();
}