#pragma once
#include "Fruit.h"
#include "Item.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        Item* itemDrop;
        int bossAttackCharge;
        int requiredBossCharge;

    public:
        Boss(string mainFile, string itemF, int requiredCharge) : Fruit(mainFile), itemDrop(new Item(itemF)), requiredBossCharge(requiredCharge) {}
        virtual string specialAttack(Fruit*) = 0;
        virtual string bossAttack(Fruit*) = 0;
        int getBossAttackCharge() { return bossAttackCharge; }
        void setBossAttackCharge(int change) { bossAttackCharge += change; }
        Item* getItem() { return itemDrop; }
        int getRequiredBossCharge() { return requiredBossCharge; }
};