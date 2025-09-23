#pragma once
#include "Boss.h"

using std::to_string;

class Dekopon : public Boss {
    public:
        Dekopon(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {
            name = "Dekopon";
            level = 50;
            stats.at(0)->addBase(2000);
            hp += 2000;
        }
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            string returnThis = calcDamage(target, true, false) + '\n';
            returnThis += calcDamage(target, false, false) + '\n';
            
            int amount = target->getStat(0) * .2;
            setHp(amount);
            if (target->getHp() <= amount) target->setHp(-1 * (target->getHp() - 1));
            else target->setHp(-1 * amount);
            return returnThis + name + ": Absorbed 20% of " + target->getName() + "\'s HP.";
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            setStatAdd(50, 0);
            setStatAdd(50, 1);
            setStatAdd(50, 2);
            setStatAdd(5, 4);
            return name + ": Stats boosted.";
        }
};