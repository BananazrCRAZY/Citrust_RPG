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
        int baseCitrusArts;
        int baseCitrusRes;
        int baseCritRate;
        double baseCritDmg;
        int maxHpAdd;
        int attackAdd;
        int defenseAdd;
        int citrusArtsAdd;
        int citrusResAdd;
        int critRateAdd;
        double critDmgAdd;
        int maxHpTotal;
        int attackTotal;
        int defenseTotal;
        int citrusArtsTotal;
        int citrusResTotal;
        int critRateTotal;
        double critDmgTotal;
        int rechargeCount;
        int turn;
        //vector<Status*> effects;

    public:
        Fruit(string);
        int basicAttack(Fruit*);
        virtual int specialAttack(Fruit*) = 0;
        int getLevel() { return level; }
        int getMaxHp() { return maxHpTotal; }
        int getHp() { return hp; }
        int getDefense() { return defenseTotal; }
        int getCitrusArts() { return citrusArtsTotal; }
        int getCitrusRes() { return citrusResTotal; }
        int getCritRate() { return critRateTotal; }
        int getCritDmg() { return critDmgTotal; }
        int getRechargeCount() { return rechargeCount; }
        int getTurn() { return turn; }
        void setMaxHpAdd(int);
        void setHp(int change) { hp += change; }
        void setDefenseAdd(int);
        void setCitrusArtsAdd(int);
        void setCitrusResAdd(int);
        void setCritRateAdd(int);
        void setCritDmgAdd(double);
        void setRechargeCount(int change) { rechargeCount += change; }
        void setTurn(int change) { turn += change; }
        //void addEffect(Status* effect) { effects.push_back(effect); }
        void endOfTurn();
};
