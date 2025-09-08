#pragma once
#include "Boss.h"

using std::to_string;

class Watermelon : public Boss {
    public:
        Watermelon(const string& main, const string& item, int required, const string& proxy) : Boss(main, item, required, proxy) {}
        string specialAttack(Fruit* target) {
            string returnStr;
            int damage = attack->getTotal() * 4 - target->getDefense();
            if (damage <= 0) returnStr = name + " did 0 damage.\n";
            target->setHp(-1*damage);
            returnStr = name + ": Dealt " + to_string(damage) + " damage.\n";

            attack->addBase(-30);
            defense->addBase(50);
            res->addBase(5);
            rechargeCount -= 2;
            return returnStr + name + ": DEF and RES increased.\n" + name + ": ATK decreased.\n";
        }

        // doesn't use
        string bossAbility() {
            return "";
        }
};