#pragma once
#include <string>
#include <vector>
#include "Status.h"

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
        vector<Status*> effects;
        bool checkIfCrit();

    public:
        Fruit(string);
        int basicAttack(Fruit*);
        virtual int specialAttack(Fruit*) = 0;
        string getName() { return name; }
        int getLevel() const { return level; }
        int getMaxHp() const { return maxHpTotal; }
        int getHp() const { return hp; }
        int getAttack() const { return attackTotal; }
        int getDefense() const { return defenseTotal; }
        int getArts() const { return ArtsTotal; }
        int getRes() const { return ResTotal; }
        int getCritRate() const { return critRateTotal; }
        int getCritDmg() const { return critDmgTotal; }
        int getRechargeCount() const { return rechargeCount; }
        int getTurn() const { return turn; }
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
        void addEffect(Status* effect) { effects.push_back(effect); }
        bool isDead() const;
        virtual int endOfTurn() = 0;
};