#pragma once
#include "Boss.h"

class Apple : public Boss {
    public:
        Apple(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            return calcDamage(target, true, false);
        }

        string bossAbility() {
            int amount = getStat(1) * .05;
            setHp(amount);
            return name + ": Healed " + std::to_string(amount) + " HP.";
        }
};