#pragma once
#include <string>
#include <vector>
#include "Stat.h"
#include "Status.h"

using std::string;
using std::vector;

class Fruit {
    protected:
        string fileName;
        string name;
        int level;
        int hp;
        Stat* maxHp;
        Stat* attack;
        Stat* defense;
        Stat* arts;
        Stat* res;
        Stat* critRate;
        Stat* critDmg;
        int rechargeCount;
        int turn;
        vector<Status*> effects;
        bool checkIfCrit();
        void removeStats(Status*);
        void addStats(Status*);
        void clearStats();

    public:
        Fruit(string);
        ~Fruit();
        string basicAttack(Fruit*);
        virtual string specialAttack(Fruit*) = 0;
        string getName() { return name; }
        int getLevel() const { return level; }
        int getMaxHp() const { return maxHp->getTotal(); }
        int getHp() const { return hp; }
        int getAttack() const { return attack->getTotal(); }
        int getDefense() const { return defense->getTotal(); }
        int getArts() const { return arts->getTotal(); }
        int getRes() const { return res->getTotal(); }
        int getCritRate() const { return critRate->getTotal(); }
        int getCritDmg() const { return critDmg->getTotal(); }
        int getRechargeCount() const { return rechargeCount; }
        int getTurn() const { return turn; }
        void setMaxHpAdd(int change) { maxHp->add(change); }
        void setHp(int change) { hp += change; }
        void setAttackAdd(int change) { attack->add(change); }
        void setDefenseAdd(int change) { defense->add(change); }
        void setArtsAdd(int change) { arts->add(change); }
        void setResAdd(int change) { res->add(change); }
        void setCritRateAdd(int change) { critRate->add(change); }
        void setCritDmgAdd(int change) { critDmg->add(change); }
        void setRechargeCount(int change) { rechargeCount += change; }
        void setTurn(int change) { turn += change; }
        void addEffect(Status*);
        bool isDead() const;
        virtual int endOfTurn();
        void clearStatus();
};