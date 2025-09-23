#pragma once
#include "include/Objects/Fruit.h"
#include "include/Objects/Item.h"
#include "include/Objects/Status.h"
#include "include/Objects/StatusManager.h"
#include <string>

using std::string;

class Boss : public Fruit {
    protected:
        int bossAbilityCharge;
        int requiredBossCharge;

    public:
        Boss(const string& mainFile, int requiredCharge, int proxyEffectId, StatusManager& statusMgr) : 
            Fruit(mainFile),
            requiredBossCharge(requiredCharge), 
            bossAbilityCharge(1)
        {
            addEffect(statusMgr.getStatus(proxyEffectId));
        }
        virtual string specialAttack(Fruit*) = 0;
        virtual string bossAbility() = 0;
        int getBossAbilityCharge() { return bossAbilityCharge; }
        int getRequiredBossCharge() { return requiredBossCharge; }
        void endOfTurn() {
            Fruit::endOfTurn();
            bossAbilityCharge++;
        }
};