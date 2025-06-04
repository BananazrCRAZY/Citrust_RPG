#pragma once
#include "Boss.h"

using std::to_string;

class Pineapple : public Boss {
    Status* effectGive = new Status("assets/status/DoT.txt");

    public:
        Pineapple(const string& main, const string& item, int required) : Boss(main, item, required) {}
        ~Pineapple() { delete effectGive; }
        string specialAttack(Fruit* target) {
            target->addEffect(effectGive);
            target->addEffect(effectGive);
            return target->getName() + ": Inflicted with DoT by " + name + ".";
        }

        // not used need to change
        string bossAbility() {
            return "";
        }

        string basicAttack(Fruit* target) override {
            string returnStr;
            int damage = arts->getTotal();
            if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
            damage = damage * (1 - (target->getRes() / 100));
            if (damage <= 0) returnStr = name + " did 0 damage.\n";
            target->setHp(-1*damage);
            returnStr = name + ": Dealt " + std::to_string(damage) + " damage.\n";

            target->addEffect(effectGive);
            return returnStr + target->getName() + ": Inflicted with DoT by " + name + ".";
        }
};