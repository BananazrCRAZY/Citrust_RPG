#pragma once
#include "include/Boss.h"

using std::to_string;

class Dekopon : public Boss {
    public:
        Dekopon(const string& main, const string& item, int required) : Boss(main, item, required) {
            name = "Dekopon";
            level = 50;
        }
        string specialAttack(Fruit* target) {
            int amount = target->getMaxHp() * .2;
            setHp(amount);
            if (target->getHp() <= amount) target->setHp(-1 * (target->getHp() - 1));
            else target->setHp(-1 * amount);
            rechargeCount -= 2;
            return name + ": Absorbed 20% of " + target->getName() + "\'s hp.";
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            setMaxHpAdd(50);
            setAttackAdd(50);
            setDefenseAdd(50);
            setResAdd(5);
            return name + ": Stats boosted.";
        }
};