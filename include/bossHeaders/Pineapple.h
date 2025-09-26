#pragma once
#include "Boss.h"
#include "include/Objects/StatusManager.h"

using std::to_string;

class Pineapple : public Boss {
    StatusManager& statusMgr;
    int dotIndex = 311;

    public:
        Pineapple(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr),
            statusMgr(statusMgr)
        {}
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            if (!checkIfHit(target)) return name + ": Missed!";
            target->addEffect(statusMgr.getStatus(dotIndex));
            target->addEffect(statusMgr.getStatus(dotIndex));
            return name + ": Wounded " + target->getName() + ".";
        }

        // not used need to change
        string bossAbility() {
            return "";
        }

        string basicAttack(Fruit* target) override {
            if (!checkIfHit(target)) return name + ": Missed!";
            string returnStr = "";
            if (checkIfAdditionRecharge()) returnStr += name + ": Obtained another SKILL POINT!\n";
            returnStr += calcDamage(target, false, true) + '\n';
            target->addEffect(statusMgr.getStatus(dotIndex));
            return returnStr + name + ": Wounded " + target->getName() + ".";
        }
};