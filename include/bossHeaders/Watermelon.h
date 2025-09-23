#pragma once
#include "Boss.h"

using std::to_string;

class Watermelon : public Boss {
    public:
        Watermelon(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            string returnStr = calcDamage(target, true, false) + '\n';
            return returnStr + calcDamage(target, false, false);
        }

        string bossAbility() {
            setStatAdd(50, 1);
            setStatAdd(40, 2);
            return name + ": ATK and DEF increased.";
        }
};