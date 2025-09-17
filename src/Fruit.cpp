#include "include/Objects/Fruit.h"
#include "include/Objects/Status.h"
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
    delete maxHp;
    maxHp = nullptr;
    delete attack;
    attack = nullptr;
    delete defense;
    defense = nullptr;
    delete arts;
    arts = nullptr;
    delete res;
    res = nullptr;
    delete critRate;
    critRate = nullptr;
    delete critDmg;
    critDmg = nullptr;
    // need to call clearEffectsVector in derived classes
}

void Fruit::clearEffectsVector() {
    for (int i = 0; i < effects.size(); i++) {
        if (effects.at(i)->isDeleteThisStatus()) {
            delete effects.at(i);
            effects.erase(effects.begin()+i);
            i--;
        }
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
    string returnThis = "";
    int damage = attack->getTotal();
    if (checkIfCrit()) {
        damage = damage * (critDmg->getTotal()/100.0 + 1);
        returnThis += "CRIT!\n";
    }
    damage = damage - target->getDefense();
    if (damage <= 0) return returnThis + name + " did 0 damage.";
    target->setHp(-1*damage);
    return returnThis + name + ": Dealt " + std::to_string(damage) + " damage.";
}

bool Fruit::checkIfCrit() {
    return ((rand() % 100) + 1) <= critRate->getTotal();
}

bool Fruit::isDead() const {
    return hp <= 0;
}

void Fruit::removeStats(Status* status) {
    if (status->isPercentBased()) {
        maxHp->add(-1 * status->getMaxHpChange()/100 * maxHp->getBase());
        attack->add(-1 * status->getAttackChange()/100 * attack->getBase());
        defense->add(-1 * status->getDefenseChange()/100 * defense->getBase());
        arts->add(-1 * status->getArtsChange()/100 * arts->getBase());
    } else {
        maxHp->add(-1 * status->getMaxHpChange());
        attack->add(-1 * status->getAttackChange());
        defense->add(-1 * status->getDefenseChange());
        arts->add(-1 * status->getArtsChange());
    }
    res->add(-1 * status->getResChange());
    critRate->add(-1 * status->getCritRateChange());
    critDmg->add(-1 * status->getCritDamageChange());

    if (hp > getMaxHp()) hp = getMaxHp();
}

void Fruit::addStats(Status* status) {
    if (status->isPercentBased()) {
        maxHp->add(status->getMaxHpChange()/100 * maxHp->getBase());
        attack->add(status->getAttackChange()/100 * attack->getBase());
        defense->add(status->getDefenseChange()/100 * defense->getBase());
        arts->add(status->getArtsChange()/100 * arts->getBase());
    } else {
        maxHp->add(status->getMaxHpChange());
        attack->add(status->getAttackChange());
        defense->add(status->getDefenseChange());
        arts->add(status->getArtsChange());
    }
    res->add(status->getResChange());
    critRate->add(status->getCritRateChange());
    critDmg->add(status->getCritDamageChange());
    setRechargeCount(status->getRechargeCountChange());
    setTurn(status->getTurnChange());
    if (hp > getMaxHp()) hp = getMaxHp();
}

void Fruit::removeEffect(Status* effect) {
    for (unsigned i = 0; i < effects.size(); i++)
        if (effects.at(i) == effect) effects.erase(effects.begin()+i);
    removeStats(effect);
}

void Fruit::addEffect(Status* effect) {
    effects.push_back(effect);
    addStats(effect);
}

// goes through effects and add to recharge, does not check dead
void Fruit::endOfTurn() {
    for (unsigned i = 0; i < effects.size(); i++) {
        if (effects.at(i)->isPercentBased()) setHp(effects.at(i)->getHpChange() * maxHp->getTotal() / 100);
        else setHp(effects.at(i)->getHpChange());

        if (effects.at(i)->getTurns() == 0) {
            removeStats(effects.at(i));
            if (effects.at(i)->isDeleteThisStatus()) delete effects.at(i);
            else effects.at(i)->resetStatusTurns();
            effects.erase(effects.begin()+i);
            i--;
        } else effects.at(i)->decreaseTurn();
    }
    setRechargeCount(1);
    turn--;
}
