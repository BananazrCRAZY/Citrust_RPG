#pragma once
#include "Boss.h"
#include <cstdlib>
#include <ctime>

class Strawberry : public Boss {
    public:
        Strawberry(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            srand(time(0));
            int defenseLower = 0;
            string returnStatement = "";
            int randNum = (rand() % 5) + 1;
            for (int i = 0; i < randNum; i++) {
                int damage = attack->getTotal();
                if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
                damage = damage - target->getDefense();
                if (damage <= 0) returnStatement += "Attack " + std::to_string(i+1) + " did 0 damage.\n";
                else {
                    target->setHp(-1 * damage);
                    returnStatement += ("Attack " + std::to_string(i+1) + " did " + std::to_string(damage) + " damage.\n");
                }
                defenseLower += (defense->getBase() * .01);
            }
            returnStatement += (name + " lost " + std::to_string(defenseLower) + " defense.");
            defense->add(-1 * defenseLower);
            return returnStatement;
        }

        // does not use target will refactor in the future
        string bossAttack(Fruit* target) {
            turn++;
            int change = defense->getBase() * .05;
            defense->add(-1 * change);
            return name + " lost " + std::to_string(change) + " defense.";
        }
};