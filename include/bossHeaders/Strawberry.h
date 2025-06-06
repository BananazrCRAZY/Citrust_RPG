#pragma once
#include "Boss.h"
#include <cstdlib>
#include <ctime>

using std::to_string;

class Strawberry : public Boss {
    public:
        Strawberry(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            srand(time(0));
            int defenseLower = 0;
            string returnStatement = "";
            int damage = attack->getTotal() - target->getDefense();
            int randNum = (rand() % 5) + 1;
            for (int i = 0; i < randNum; i++) {
                if (damage <= 0) returnStatement += (name + ": Attack " + to_string(i+1) + " did 0 damage.\n");
                else {
                    target->setHp(-1 * damage);
                    returnStatement += (name + ": Attack " + to_string(i+1) + " did " + to_string(damage) + " damage.\n");
                }
                defenseLower += (defense->getBase() * .01);
            }
            returnStatement += (name + ": Lost " + to_string(defenseLower) + " defense.");
            defense->add(-1 * defenseLower);

            rechargeCount -= 2;
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            int change = defense->getBase() * .03;
            defense->add(-1 * change);
            return name + ": Lost " + to_string(change) + " defense.";
        }
};