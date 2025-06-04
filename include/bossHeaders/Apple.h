#pragma once
#include "Boss.h"

class Apple : public Boss {
    public:
        Apple(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            int damage = attack->getTotal() * 2;
            if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
            damage = damage - target->getDefense();
            if (damage <= 0) return name + " did 0 damage.";
            target->setHp(-1*damage);
            return name + " did " + std::to_string(damage) + " damage.";
        }

        // does not use target will refactor in the future
        string bossAttack(Fruit* target) {
            int amount = maxHp->getTotal() * .05;
            setHp(amount);
            return "Apple healed " + std::to_string(amount) + " hp.";
        }
};