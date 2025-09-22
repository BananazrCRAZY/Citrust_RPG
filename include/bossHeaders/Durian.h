#pragma once
#include "Boss.h"
#include "include/Objects/Status.h"
#include "include/Objects/StatusManager.h"
#include <string>

using std::string;
using std::to_string;

class Durian : public Boss {
    StatusManager& statusMgr;
    int damageTaken = 0;

    public:
        Durian(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr), statusMgr(statusMgr) {
            addEffect(statusMgr.getStatus(208));
        }

        string specialAttack(Fruit* target) {
            string returnThis = "";
            int damage = attack->getTotal() * 3;
            if (checkIfCrit()) {
                returnThis += "CRIT!\n";
                damage *= (critDmg->getTotal() / 100.0 + 1);
            }
            damage = damage - (target->getDefense() * .5);
            if (damage <= 0) return returnThis + name + " did 0 damage.";
            target->setHp(-1*damage);
            rechargeCount -= 2;
            return returnThis + name + ": Dealt " + to_string(damage) + " damage.";
        }

        string bossAbility() {
            // really simplistic calculation that doesn't take into account if boss hp/max changes
            int change = maxHp->getBase() - hp - damageTaken;
            damageTaken = maxHp->getBase() - hp;
            if (change <= 0) return name + ": Waiting for a chance to counter.";
            attack->add(static_cast<int>(change * .03));
            return name + ": Getting angry.";
        }

        string basicAttack(Fruit* target) override {
            string returnStr = Fruit::basicAttack(target) + '\n';

            target->addEffect(statusMgr.getStatus(308));
            return returnStr + name + ": Wounded " + target->getName() + ".";
        }
};