#pragma once
#include "Boss.h"
#include "include/Objects/StatusManager.h"

using std::to_string;

class Pineapple : public Boss {
    StatusManager& statusMgr;

    public:
        Pineapple(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr),
            statusMgr(statusMgr)
        {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            target->addEffect(statusMgr.getStatus(307));
            target->addEffect(statusMgr.getStatus(307));
            return name + ": Wounded " + target->getName() + ".";
        }

        // not used need to change
        string bossAbility() {
            return "";
        }

        string basicAttack(Fruit* target) override {
            string returnStr;
            int damage = arts->getTotal();
            if (checkIfCrit()) {
                damage = damage * (critDmg->getTotal()/100.0 + 1);
                returnStr += "CRIT!\n";
            }
            damage *= (1 - (target->getRes()/100.0));
            if (damage <= 0) returnStr = name + " did 0 damage.\n";
            target->setHp(-1*damage);
            returnStr = name + ": Dealt " + std::to_string(damage) + " damage.\n";

            target->addEffect(statusMgr.getStatus(307));
            return returnStr + name + ": Wounded " + target->getName() + ".";
        }
};