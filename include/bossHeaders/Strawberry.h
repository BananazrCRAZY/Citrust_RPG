#pragma once
#include "Boss.h"
#include <cstdlib>
#include <ctime>

using std::to_string;

class Strawberry : public Boss {
    public:
        Strawberry(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            int defenseLower = 0;
            string returnStatement = "";
            int damage = getStat(2) * (getStat(10) / 100.0 + 1) - target->getStat(2);
            double dmgMultiplier = (getStat(11) - getStat(12)) / 100.0;
            if (dmgMultiplier < -1) dmgMultiplier = -1;
            damage *= (1 + dmgMultiplier) * (1 + target->getStat(13) / 100.0);
            int randNum = (rand() % 5) + 1;
            for (int i = 0; i < randNum; i++) {
                if (damage <= 0) returnStatement += (name + ": Attack " + to_string(i+1) + " did 0 damage.\n");
                else {
                    target->setHp(-1 * damage);
                    returnStatement += (name + ": Attack " + to_string(i+1) + " did " + to_string(damage) + " damage.\n");
                }
                defenseLower += (stats.at(2)->getBase() * .01);
            }
            returnStatement += (name + ": Lost " + to_string(defenseLower) + " DEF.");
            setStatAdd(-1 * defenseLower, 2);
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            int change = stats.at(2)->getBase() * .03;
            setStatAdd(-1 * change, 2);
            return name + ": Lost " + to_string(change) + " DEF.";
        }
};