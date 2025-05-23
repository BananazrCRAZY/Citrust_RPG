#pragma once
#include <string>
#include <vector>
//#include "Status.h"

using std::string;
using std::vector;

class Fruit {
    protected:
        string fileName;
        string name;
        int level;
        int hp;
        int baseMaxHp;
        int baseAttack;
        int baseDefense;
        int baseArts;
        int baseRes;
        int baseCritRate;
        double baseCritDmg;
        int maxHpAdd;
        int attackAdd;
        int defenseAdd;
        int ArtsAdd;
        int ResAdd;
        int critRateAdd;
        double critDmgAdd;
        int maxHpTotal;
        int attackTotal;
        int defenseTotal;
        int ArtsTotal;
        int ResTotal;
        int critRateTotal;
        double critDmgTotal;
        int rechargeCount;
        int turn;
        //vector<Status*> effects;

    public:
        Fruit(string);
        int basicAttack(Fruit*);
        virtual int specialAttack(Fruit*) = 0;
        string getName() { return name; }
        int getLevel() { return level; }
        int getMaxHp() { return maxHpTotal; }
        int getHp() { return hp; }
        int getAttack() { return attackTotal; }
        int getDefense() { return defenseTotal; }
        int getArts() { return ArtsTotal; }
        int getRes() { return ResTotal; }
        int getCritRate() { return critRateTotal; }
        int getCritDmg() { return critDmgTotal; }
        int getRechargeCount() { return rechargeCount; }
        int getTurn() { return turn; }
        void setMaxHpAdd(int);
        void setHp(int change) { hp += change; }
        void setAttackAdd(int);
        void setDefenseAdd(int);
        void setArtsAdd(int);
        void setResAdd(int);
        void setCritRateAdd(int);
        void setCritDmgAdd(double);
        void setRechargeCount(int change) { rechargeCount += change; }
        void setTurn(int change) { turn += change; }
        //void addEffect(Status* effect) { effects.push_back(effect); }
        void endOfTurn();
};
