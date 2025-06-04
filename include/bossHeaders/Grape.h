#pragma once
#include "Boss.h"

using std::to_string;

class Grape : public Boss {
    Status* effectGive = new Status();

    public:
        Grape(const string& main, const string& item, int required) : Boss(main, item, required) {}
        ~Grape() { delete effectGive; }
        string specialAttack(Fruit* target) {
            srand(time(0));
            string returnStatement = "";
            for (int i = 1; i < 4; i++) {
                int damage = arts->getTotal() * (1-(target->getRes()/100));
                target->setHp(-1 * damage);
                returnStatement += (name + ": Attack " + to_string(i) + " did " + to_string(damage) + " damage.\n");
                if ((rand() % 5) > 2) {
                    target->addEffect(effectGive);
                    returnStatement += (name + ": Gave " + target->getName() + " " + effectGive->getName() + ".");
                }
            }
            rechargeCount -= 2;
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            turn++;
            return name + ": Charged up.";
        }
};