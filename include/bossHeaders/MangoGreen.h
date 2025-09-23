#pragma once
#include "Boss.h"

using std::to_string;

class MangoGreen : public Boss {
    public:
        MangoGreen(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            string returnStr = calcDamage(target, true, false) + '\n';
            target->setStatAdd(-20, 1);
            return returnStr + name + ": Decreased " + target->getName() + "'s ATK.";
        }

        // checks to see if hp is below 50% to start 2nd half of fight
        string bossAbility() {
            if (hp < (getStat(0) / 2)) {
                hp = 0;
                return name + " Is Getting Furious!";
            }
            return "";
        }
};