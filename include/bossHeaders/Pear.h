#pragma once
#include "Boss.h"

class Pear : public Boss {
    public:
        Pear(const string& main, const string& item, int required, const string& proxy) : Boss(main, item, required, proxy) {}
        string specialAttack(Fruit* target) {
            string returnThis = "";
            rechargeCount -= 2;
            int damage = attack->getTotal() * 2;
            if (checkIfCrit()) {
                returnThis += "CRIT!\n";
                damage *= (critDmg->getTotal() / 100.0 + 1);
            }
            damage -= target->getDefense();
            if (damage <= 0) return returnThis + name + ": Dealt 0 damage.";
            target->setHp(-1*damage);
            
            return returnThis + name + ": Dealt " + std::to_string(damage) + " damage.";
        }

        string bossAbility() {
            critDmg->add(25);
            return name + ": CRIT DMG Increased.";
        }
};