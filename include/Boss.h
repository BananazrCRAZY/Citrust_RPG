#pragma once
#include "Fruit.h"
//#include "Item.h"
#include <string>

using std::string;

class Boss : public Fruit {
    //Item* itemDrop;
    int bossAttackCharge;

    public:
        Boss(string file);
        int specialAttack(Fruit*);
        void bossAttack(Fruit*);
        int getBossAttackCharge() { return bossAttackCharge; }
        void setBossAttackCharge(int change) { bossAttackCharge += change; }
        //Item* getItem() { return itemDrop; }
        void endOfTurn();
};