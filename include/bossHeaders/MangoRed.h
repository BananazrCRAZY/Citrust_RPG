#pragma once
#include "Boss.h"

using std::to_string;

class MangoRed : public Boss {
    public:
        MangoRed(const string& main, const string& item, int required, const string& proxy) : Boss(main, item, required, proxy) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            string returnStr = "";
            int damage = arts->getTotal() * (1 - (target->getRes() / 100.0));
            if (damage <= 0) returnStr += (name + ": Dealt 0 damage.\n");
            else {
                target->setHp(-1*damage);
                returnStr += (name + ": Dealt " + std::to_string(damage) + " damage.\n");
            }
            target->setAttackAdd(-30);
            return returnStr + name + ": Decreased " + target->getName() + "'s ATK.";
        }

        string bossAbility() {
            if (hp < (maxHp->getTotal() / 2)) {
                requiredBossCharge = 101;
                attack->add(150);
                return name + ": ATK increased.";
            }
            return "";
        }
};