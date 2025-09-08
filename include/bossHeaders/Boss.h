#pragma once
#include "include/Objects/Fruit.h"
#include "include/Objects/Item.h"
#include "include/Objects/Status.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        Item* itemDrop;
        int bossAbilityCharge;
        int requiredBossCharge;

    public:
        Boss(const string& mainFile, const string& itemF, int requiredCharge, const string& proxyEffect) : 
            Fruit(mainFile), 
            itemDrop(new Item(itemF)), 
            requiredBossCharge(requiredCharge), 
            bossAbilityCharge(1)
        {
            addEffect(new Status(proxyEffect));
        }
        ~Boss() {
            clearEffectsVector();
            effects.clear();
        }
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