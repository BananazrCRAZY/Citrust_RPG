#pragma once
#include "Boss.h"

using std::to_string;

class Dekopon : public Boss {
    public:
        Dekopon(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {
            name = "Dekopon";
            level = 50;
            maxHp->addBase(2000);
            hp += 2000;
        }
        string specialAttack(Fruit* target) {
            string returnThis = "";
            int physDmg = attack->getTotal();
            int artsDmg = arts->getTotal();
            if (checkIfCrit()) {
                physDmg *= (critDmg->getTotal()/100.0 + 1);
                artsDmg *= (critDmg->getTotal()/100.0 + 1);
                returnThis += "CRIT!\n";
            }
            physDmg -= target->getDefense();
            if (physDmg <= 0) physDmg = 0;
            artsDmg *= (1.0 - (target->getRes()/100.0));
            if (artsDmg <= 0) artsDmg = 0;
            int damageDealt = physDmg + artsDmg;
            if (damageDealt <= 0) returnThis += name + ": Dealt 0 damage.\n";
            else {
                target->setHp(-1 * damageDealt);
                returnThis += name + ": Dealt " + std::to_string(damageDealt) + " damage.\n";
            }
            int amount = target->getMaxHp() * .2;
            setHp(amount);
            if (target->getHp() <= amount) target->setHp(-1 * (target->getHp() - 1));
            else target->setHp(-1 * amount);
            rechargeCount -= 2;
            return returnThis + name + ": Absorbed 20% of " + target->getName() + "\'s HP.";
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