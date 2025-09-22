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
        vector<Stat*> stats;
        int rechargeCount;
        int turn;
        vector<Status*> effects;
        bool checkIfCrit();
        bool checkIfHit(Fruit*);
        void checkIfAdditionRecharge();
        void removeStats(Status*);
        void addStats(Status*);
        
        void clearStats();
        void reAddStats();  // called by levelUp()

    public:
        Fruit(const string&);
        virtual ~Fruit();
        virtual string basicAttack(Fruit*);
        virtual string specialAttack(Fruit*) = 0;
        string getName() { return name; }
        int getLevel() const { return level; }
        int getHp() const { return hp; }
        int getStat(unsigned index) const;
        int getRechargeCount() const { return rechargeCount; }
        int getTurn() const { return turn; }
        Status* getEffect(unsigned index) const { return effects.at(index); }
        unsigned getNumberOfEffects() const { return effects.size(); }
        void setHp(int change);
        void setStatAdd(int change, unsigned index);
        void setRechargeCount(int change) {
            rechargeCount += change;
            if (rechargeCount < 0) rechargeCount = 0;
            if (rechargeCount > 5) rechargeCount = 5;
        }
        void setTurn(int change) { turn += change; }
        void removeEffect(Status*);
        void addEffect(Status*);
        bool isDead() const;
        void endOfTurn();
};
