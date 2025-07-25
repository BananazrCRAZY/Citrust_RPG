#include "include/Fruit.h"
#include "include/Status.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

using std::cerr;
using std::srand;
using std::rand;
using std::time;

Fruit::Fruit(const string& file) : 
    fileName(file),
    rechargeCount(2),
    turn(1)
    {
        std::ifstream iFile(fileName);
        if (!iFile.good()) {
            cerr << "Error with opening Fruit file fstream" << std::endl;
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
            cerr << "Error with Fruit file format fstream" << std::endl;
            exit(1);
        }
        iFile.close();
    }

Fruit::~Fruit() {
    clearEffectsVector();
    delete maxHp;
    delete attack;
    delete defense;
    delete arts;
    delete res;
    delete critRate;
    delete critDmg;
}

void Fruit::clearEffectsVector() {
    for (unsigned i = 0; i < effects.size(); i++) {
        if (effects.at(i)->isDeleteThisStatus()) delete effects.at(i);
    }
}

void Fruit::setMaxHpAdd(int change) {
    maxHp->add(change);
    if (change > 0) setHp(change);
    if (hp > maxHp->getTotal()) hp = maxHp->getTotal();
}

void Fruit::setHp(int change) {
    hp += change;
    if (hp > maxHp->getTotal()) hp = maxHp->getTotal();
}

string Fruit::basicAttack(Fruit* target) {
    int damage = attack->getTotal();
    if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100.0 + 1);
    damage = damage - target->getDefense();
    if (damage <= 0) return name + " did 0 damage.";
    target->setHp(-1*damage);
    return name + ": Dealt " + std::to_string(damage) + " damage.";
}

bool Fruit::checkIfCrit() {
    return ((rand() % 100) + 1) <= critRate->getTotal();
}

bool Fruit::isDead() const {
    return hp <= 0;
}

void Fruit::removeStats(Status* status) {
    if (status->isPercentBased()) {
        setMaxHpAdd(-1 * status->getMaxHpChange()/100 * maxHp->getBase());
        attack->add(-1 * status->getAttackChange()/100 * attack->getBase());
        defense->add(-1 * status->getDefenseChange()/100 * defense->getBase());
        arts->add(-1 * status->getArtsChange()/100 * arts->getBase());
    } else {
        setMaxHpAdd(-1 * status->getMaxHpChange());
        attack->add(-1 * status->getAttackChange());
        defense->add(-1 * status->getDefenseChange());
        arts->add(-1 * status->getArtsChange());
    }
    res->add(-1 * status->getResChange());
    critRate->add(-1 * status->getCritRateChange());
    critDmg->add(-1 * status->getCritDamageChange());
}

void Fruit::addStats(Status* status) {
    if (status->isPercentBased()) {
        setMaxHpAdd(status->getMaxHpChange()/100 * maxHp->getBase());
        attack->add(status->getAttackChange()/100 * attack->getBase());
        defense->add(status->getDefenseChange()/100 * defense->getBase());
        arts->add(status->getArtsChange()/100 * arts->getBase());
    } else {
        setMaxHpAdd(status->getMaxHpChange());
        attack->add(status->getAttackChange());
        defense->add(status->getDefenseChange());
        arts->add(status->getArtsChange());
    }
    res->add(status->getResChange());
    critRate->add(status->getCritRateChange());
    critDmg->add(status->getCritDamageChange());
    setRechargeCount(status->getRechargeCountChange());
    setTurn(status->getTurnChange());
}

void Fruit::addEffect(Status* effect) {
    effects.push_back(effect);
    addStats(effect);
}

// goes through effects and add to recharge, does not check dead
void Fruit::endOfTurn() {
    for (unsigned i = 0; i < effects.size(); i++) {
        if (effects.at(i)->getTurns() == 0) {
            removeStats(effects.at(i));
            if (effects.at(i)->isDeleteThisStatus()) delete effects.at(i);
            else effects.at(i)->resetStatusTurns();
            effects.erase(effects.begin()+i);
        } else {
            if (effects.at(i)->isPercentBased()) setHp(effects.at(i)->getHpChange() * maxHp->getTotal());
            else setHp(effects.at(i)->getHpChange());
            effects.at(i)->decreaseTurn();
        }
    }
    setRechargeCount(1);
    turn--;
}
