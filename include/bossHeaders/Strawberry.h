#pragma once
#include "Boss.h"
#include <cstdlib>
#include <ctime>

using std::to_string;

class Strawberry : public Boss {
    int multiAttackCount;

    public:
        Strawberry(const string& main, int required, int proxy, StatusManager& statusMgr) :
            Boss(main, required, proxy, statusMgr),
            multiAttackCount(0)
        {}

        string specialAttack(Fruit* target) {
            string returnStatement = "";
            int defenseLower = 0;
            rechargeCount--;

            if (multiAttackCount == 0) {
                multiAttackCount = (rand() % 5) + 1;
                turn += (multiAttackCount - 1);
                returnStatement += name + " is ready to burst " + to_string(multiAttackCount) + " times!\n";
            }
            if (multiAttackCount == 1) rechargeCount--;

            int damage = getStat(2) * (getStat(10) / 100.0 + 1) - target->getStat(2);
            double dmgMultiplier = (getStat(11) - getStat(12)) / 100.0;
            if (dmgMultiplier < -1) dmgMultiplier = -1;
            damage *= (1 + dmgMultiplier) * (1 + target->getStat(13) / 100.0);
            if (damage <= 0) returnStatement += (name + ": Dealt 0 damage.\n");
            else returnStatement += (name + ": Dealt " + to_string(damage) + " damage.\n");
            target->setHp(-1 * damage);

            defenseLower += (stats.at(2)->getBase() * .01);
            returnStatement += (name + ": Lost " + to_string(defenseLower) + " DEF.");
            setStatAdd(-1 * defenseLower, 2);

            multiAttackCount--;
            return returnStatement;
        }

        string basicAttack(Fruit* target) override {
            string returnStatement = "";
            int defenseLower = 0;

            int damage = getStat(2) * (getStat(9) / 100.0 + 1) - target->getStat(2);
            double dmgMultiplier = (getStat(11) - getStat(12)) / 100.0;
            if (dmgMultiplier < -1) dmgMultiplier = -1;
            damage *= (1 + dmgMultiplier) * (1 + target->getStat(13) / 100.0);
            if (damage <= 0) returnStatement += (name + ": Dealt 0 damage.\n");
            else returnStatement += (name + ": Dealt " + to_string(damage) + " damage.\n");
            target->setHp(-1 * damage);

            defenseLower += (stats.at(2)->getBase() * .01);
            returnStatement += (name + ": Lost " + to_string(defenseLower) + " DEF.");
            setStatAdd(-1 * defenseLower, 2);

            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            int change = stats.at(2)->getBase() * .02;
            setStatAdd(-1 * change, 2);
            return name + ": Lost " + to_string(change) + " DEF.";
        }
};