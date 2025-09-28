#pragma once
#include "Boss.h"
#include "include/Objects/Status.h"
#include "include/Objects/StatusManager.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::to_string;

class Grape : public Boss {
    StatusManager& statusMgr;
    int multiAttackCount;

    public:
        Grape(const string& main, int required, int proxy, StatusManager& statusMgr) :
            Boss(main, required, proxy, statusMgr), statusMgr(statusMgr),
            multiAttackCount(0)
        {}

        string specialAttack(Fruit* target) {
            string returnStatement = "";
            rechargeCount--;

            if (multiAttackCount == 0) {
                multiAttackCount = (rand() % 4) + 1;
                turn += (multiAttackCount - 1);
                returnStatement += name + " is ready to burst " + to_string(multiAttackCount) + " times!\n";
            }
            if (multiAttackCount == 1) rechargeCount--;

            returnStatement += calcDamage(target, false, false);
            if ((rand() % 5) > 2) {
                int effectIndex = rand() % 10;
                target->addEffect(statusMgr.getStatus(effectIndex + 301));
                returnStatement += '\n' + name + ": Gave " + target->getName() + " a random effect.";
            }

            multiAttackCount--;
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            turn++;
            return name + ": Charged up.";
        }
};