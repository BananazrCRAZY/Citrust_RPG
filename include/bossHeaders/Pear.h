#pragma once
#include "Boss.h"

class Pear : public Boss {
    public:
        Pear(const string& main, const string& item, int required) : Boss(main, item, required) {}
        string specialAttack(Fruit* target) {
            int damage = arts->getTotal() * 2;
            if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
            damage *= (1-(target->getRes()/100));
            if (damage <= 0) return name + ": Dealt 0 damage.";
            target->setHp(-1*damage);
            
            rechargeCount -= 2;
            return name + ": Dealt " + std::to_string(damage) + " damage.";
        }

        string bossAbility() {
            critRate->add(2);
            return name + ": Increased critical rate.";
        }
};