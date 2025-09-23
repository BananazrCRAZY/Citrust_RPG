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
            string returnStr = calcDamage(target, false, true);
            target->addEffect(statusMgr.getStatus(307));
            return returnStr + name + ": Wounded " + target->getName() + ".";
        }
};