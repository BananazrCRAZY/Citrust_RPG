#pragma once
#include "Boss.h"

using std::to_string;

class MangoGreen : public Boss {
    public:
        MangoGreen(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            string returnStr = "";
            int damage = attack->getTotal() * .5 - target->getDefense();
            if (damage <= 0) returnStr += (name + ": Dealt 0 damage.\n");
            else {
                target->setHp(-1*damage);
                returnStr += (name + ": Dealt " + std::to_string(damage) + " damage.\n");
            }
            target->setAttackAdd(-20);
            return returnStr + target->getName() + ": Attack decreased by " + name + ".";
        }

        string bossAbility() {
            if (hp < (maxHp->getTotal() / 2)) {
                requiredBossCharge = 101;
                attack->add(100);
                return name + ": Attack increased.";
            }
            return "";
        }
};