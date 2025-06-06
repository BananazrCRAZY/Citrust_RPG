#pragma once
#include "include/Boss.h"

using std::to_string;

class MangoGreen : public Boss {
    public:
        MangoGreen(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            string returnStr = "";
            int damage = attack->getTotal() * .5 - target->getDefense();
            if (damage <= 0) returnStr += (name + " did 0 damage.\n");
            target->setHp(-1*damage);
            returnStr += (name + ": Dealt " + std::to_string(damage) + " damage.\n");
            target->setAttackAdd(-25);
            rechargeCount -= 2;
            return returnStr + target->getName() + ": Attack decreased by " + name + ".";
        }

        string bossAbility() {
            if (hp < (maxHp->getTotal() / 2)) {
                requiredBossCharge = 101;
                attack->add(500);
                return name + ": Attack increased.";
            }
            return "";
        }
};