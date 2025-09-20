#pragma once
#include "include/Objects/Fruit.h"
#include "include/Objects/Item.h"
#include "include/Objects/Status.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        Item* itemDrop = nullptr;
        int bossAbilityCharge;
        int requiredBossCharge;

    public:
        Boss(const string& mainFile, int requiredCharge, const string& proxyEffect) : 
            Fruit(mainFile),
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