#pragma once
#include "Fruit.h"
//#include "Item.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        //Item* itemDrop;
        int bossAttackCharge;
        string itemFile;

    public:
        Boss(string, string);
        virtual int specialAttack(Fruit*) = 0;
        virtual int bossAttack(Fruit*) = 0;
        int getBossAttackCharge() { return bossAttackCharge; }
        void setBossAttackCharge(int change) { bossAttackCharge += change; }
        //Item* getItem() { return itemDrop; }
        void endOfTurn();
};