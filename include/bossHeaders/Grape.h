#pragma once
#include "Boss.h"
#include "include/Objects/Status.h"
#include "include/Objects/StatusManager.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::to_string;

class Grape : public Boss {
    StatusManager& statusMgr;

    public:
        Grape(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr), statusMgr(statusMgr) {}

        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            string returnStatement = "";
            int damage = arts->getTotal() * (1-(target->getRes()/100.0));
            for (int i = 1; i < 4; i++) {
                target->setHp(-1 * damage);
                returnStatement += (name + ": Attack " + to_string(i) + " did " + to_string(damage) + " damage.\n");
                if ((rand() % 5) > 2) {
                    int effectIndex = rand() % 6;
                    target->addEffect(statusMgr.getStatus(effectIndex + 301));
                    returnStatement += (name + ": Gave " + target->getName() + " a random effect.\n");
                }
            }
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            turn++;
            return name + ": Charged up.";
        }
};