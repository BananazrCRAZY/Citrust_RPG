#pragma once
#include "Boss.h"

class Pear : public Boss {
    public:
        Pear(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            return calcDamage(target, true, false);
        }

        string bossAbility() {
            setStatAdd(25, 6);
            return name + ": CRIT DMG Increased.";
        }
};