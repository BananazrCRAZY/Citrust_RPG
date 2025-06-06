#pragma once
#include "Boss.h"

using std::to_string;

class Durian : public Boss {
    Status* effectGive = new Status("assets/status/DoTPercent.txt");
    int damageTaken = 0;

    public:
        Durian(const string& main, const string& item, int required) : Boss(main, item, required) {}
        ~Durian() { delete effectGive; }
        string specialAttack(Fruit* target) {
            int damage = attack->getTotal() * 3;
            if (checkIfCrit()) damage = damage * (critDmg->getTotal()/100 + 1);
            damage = damage - (target->getDefense() * .5);
            if (damage <= 0) return name + " did 0 damage.";
            target->setHp(-1*damage);
            rechargeCount -= 2;
            return name + ": Dealt " + to_string(damage) + " damage.";
        }

        string bossAbility() {
            // really simplistic calculation that doesn't take into account if boss hp/max changes
            int change = maxHp->getBase() - hp - damageTaken;
            if (change <= 0) return "";
            attack->add(change * .1);
            return name + ": Getting angry.";
        }

        string basicAttack(Fruit* target) override {
            string returnStr = Fruit::basicAttack(target) + '\n';

            target->addEffect(effectGive);
            return returnStr + target->getName() + ": Inflicted with DoT by " + name + ".";
        }
};