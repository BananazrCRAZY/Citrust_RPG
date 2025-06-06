#pragma once
#include "include/Boss.h"

class Apple : public Boss {
    public:
        Apple(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            int damage = attack->getTotal() * 2 - target->getDefense();
            if (damage <= 0) return name + " did 0 damage.";
            target->setHp(-1*damage);
            rechargeCount -= 2;
            return name + ": Dealt " + std::to_string(damage) + " damage.";
        }

        string bossAbility() {
            int amount = maxHp->getTotal() * .05;
            setHp(amount);
            rechargeCount -= 2;
            return name + ": Healed " + std::to_string(amount) + " hp.";
        }
};