#pragma once
#include "Fruit.h"
#include "Item.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        Item* itemDrop;
        int bossAbilityCharge;
        int requiredBossCharge;

    public:
        Boss(const string& mainFile, const string& itemF, int requiredCharge) : 
            Fruit(mainFile), 
            itemDrop(new Item(itemF)), 
            requiredBossCharge(requiredCharge), 
            bossAbilityCharge(1) {}
        virtual string specialAttack(Fruit*) = 0;
        virtual string bossAbility() = 0;
        int getBossAbilityCharge() { return bossAbilityCharge; }
        Item* getItem() { return itemDrop; }
        int getRequiredBossCharge() { return requiredBossCharge; }
        void endOfTurn() {
            Fruit::endOfTurn();
            bossAbilityCharge++;
        }
};