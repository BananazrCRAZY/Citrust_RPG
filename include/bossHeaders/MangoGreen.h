#pragma once
#include "Boss.h"

using std::to_string;

class MangoGreen : public Boss {
    public:
        MangoGreen(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
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
            return returnStr + name + ": Decreased " + target->getName() + "'s ATK.";
        }

        // checks to see if hp is below 50% to start 2nd half of fight
        string bossAbility() {
            if (hp < (maxHp->getTotal() / 2)) {
                hp = 0;
                return name + " Is Getting Furious!";
            }
            return "";
        }
};