#pragma once
#include "Fruit.h"
#include "Item.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        Item* itemDrop;
        int bossAttackCharge;
        string itemFile;

    public:
        Boss(string, string);
        virtual int specialAttack(Fruit*);
        int getBossAttackCharge() { return bossAttackCharge; }
        void setBossAttackCharge(int change) { bossAttackCharge += change; }
        Item* getItem() { return itemDrop; }
        int endOfTurn();
};