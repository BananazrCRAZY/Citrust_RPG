#pragma once
#include "Boss.h"

class Pear : public Boss {
    public:
        Pear(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            int damage = attack->getTotal() * 2;
            if (checkIfCrit()) damage *= (critDmg->getTotal() / 100.0 + 1);
            damage -= target->getDefense();
            if (damage <= 0) return name + ": Dealt 0 damage.";
            target->setHp(-1*damage);
            
            return name + ": Dealt " + std::to_string(damage) + " damage.";
        }

        string bossAbility() {
            critRate->add(2);
            return name + ": Increased critical rate.";
        }
};