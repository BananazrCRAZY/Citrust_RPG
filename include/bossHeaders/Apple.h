#pragma once
#include "Boss.h"

class Apple : public Boss {
    public:
        Apple(const string& main, const string& item, int required, const string& proxy) : Boss(main, item, required, proxy) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            int damage = attack->getTotal() * 2 - target->getDefense();
            if (damage <= 0) return name + ": Dealt 0 damage.";
            target->setHp(-1*damage);
            return name + ": Dealt " + std::to_string(damage) + " damage.";
        }

        string bossAbility() {
            int amount = maxHp->getTotal() * .05;
            setHp(amount);
            return name + ": Healed " + std::to_string(amount) + " HP.";
        }
};