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
        while (iFile >> output) stats.push_back(new Stat(output));

        if (!iFile.good()) {
            cerr << "Error with Fruit file format fstream" << std::endl;
            exit(1);
        }
        iFile.close();
    }

Fruit::~Fruit() {
    for (Stat* stat : stats) delete stat;
}

void Fruit::setHp(int change) {
    hp += change;
    if (hp > getStat(0)) hp = getStat(0);
}

void Fruit::setStatAdd(int change, unsigned index) {
    if (index >= stats.size()) {
        cerr << "Error: Fruit.cpp, setStat(), index is too large\n";
        exit(1);
    }
    stats.at(index)->add(change);
}

int Fruit::getStat(unsigned index) const {
    if (index >= stats.size()) {
        cerr << "Error: Fruit.cpp, getStat(), index is too large\n";
        exit(1);
    }
    return stats.at(index)->getTotal();
}

string Fruit::basicAttack(Fruit* target) {
    string returnThis = "";
    int damage = getStat(1);
    if (checkIfCrit()) {
        damage = damage * (getStat(6)/100.0 + 1);
        returnThis += "CRIT!\n";
    }
    // damage = (damage * basicDmg - def) * (1 + (dmgAmp - weakness) / 100)
    double dmgMultiplier = (getStat(11) - getStat(12)) / 100.0;
    if (dmgMultiplier < 0) dmgMultiplier = 0;
    damage = (damage * getStat(9) - target->getStat(2)) * (1 + dmgMultiplier);

    if (damage <= 0) return returnThis + name + ": Dealt 0 damage.";
    target->setHp(-1*damage);
    return returnThis + name + ": Dealt " + std::to_string(damage) + " damage.";
}

bool Fruit::checkIfCrit() {
    // crit rate + intellect / 2
    return ((rand() % 100) + 1) <= (getStat(5) + getStat(8) / 2);
}

bool Fruit::isDead() const {
    return hp <= 0;
}

void Fruit::removeStats(Status* status) {
    if (status->isPercentBased()) {
        setStatAdd(-1 * status->getMaxHpChange()/100 * stats.at(0)->getBase(), 0);
        setStatAdd(-1 * status->getAttackChange()/100 * stats.at(1)->getBase(), 1);
        setStatAdd(-1 * status->getDefenseChange()/100 * stats.at(2)->getBase(), 2);
        setStatAdd(-1 * status->getArtsChange()/100 * stats.at(3)->getBase(), 3);
    } else {
        setStatAdd(-1 * status->getMaxHpChange(), 0);
        setStatAdd(-1 * status->getAttackChange(), 1);
        setStatAdd(-1 * status->getDefenseChange(), 2);
        setStatAdd(-1 * status->getArtsChange(), 3);
    }
    setStatAdd(-1 * status->getResChange(), 4);
    setStatAdd(-1 * status->getCritRateChange(), 5);
    setStatAdd(-1 * status->getCritDamageChange(), 6);
    setStatAdd(-1 * status->getEvasionChange(), 7);
    setStatAdd(-1 * status->getIntellectChange(), 8);
    setStatAdd(-1 * status->getBasicDmgChange(), 9);
    setStatAdd(-1 * status->getSkillDmgChange(), 10);
    setStatAdd(-1 * status->getDmgAmpChange(), 11);
    setStatAdd(-1 * status->getWeaknessChange(), 12);
    setStatAdd(-1 * status->getVulnerabilityChange(), 13);

    if (hp > getStat(0)) hp = getStat(0);
}

void Fruit::addStats(Status* status) {
    if (status->isPercentBased()) {
        setStatAdd(status->getMaxHpChange()/100 * stats.at(0)->getBase(), 0);
        setStatAdd(status->getAttackChange()/100 * stats.at(1)->getBase(), 1);
        setStatAdd(status->getDefenseChange()/100 * stats.at(2)->getBase(), 2);
        setStatAdd(status->getArtsChange()/100 * stats.at(3)->getBase(), 3);
    } else {
        setStatAdd(status->getMaxHpChange(), 0);
        setStatAdd(status->getAttackChange(), 1);
        setStatAdd(status->getDefenseChange(), 2);
        setStatAdd(status->getArtsChange(), 3);
    }
    setStatAdd(status->getResChange(), 4);
    setStatAdd(status->getCritRateChange(), 5);
    setStatAdd(status->getCritDamageChange(), 6);
    setStatAdd(status->getEvasionChange(), 7);
    setStatAdd(status->getIntellectChange(), 8);
    setStatAdd(status->getBasicDmgChange(), 9);
    setStatAdd(status->getSkillDmgChange(), 10);
    setStatAdd(status->getDmgAmpChange(), 11);
    setStatAdd(status->getWeaknessChange(), 12);
    setStatAdd(status->getVulnerabilityChange(), 13);

    if (hp > getStat(0)) hp = getStat(0);

    setRechargeCount(status->getRechargeCountChange());
    setTurn(status->getTurnChange());
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
        if (effects.at(i)->isPercentBased()) setHp(effects.at(i)->getHpChange() * getStat(0) / 100);
        else setHp(effects.at(i)->getHpChange());

        if (effects.at(i)->getTurns() == 0) {
            removeStats(effects.at(i));
            if (!effects.at(i)->isDeleteThisStatus()) effects.at(i)->resetStatusTurns();
            effects.erase(effects.begin()+i);
            i--;
        } else effects.at(i)->decreaseTurn();
    }
    setRechargeCount(1);
    turn--;
}
