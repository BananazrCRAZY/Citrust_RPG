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
            if (!checkIfHit(target)) return name + ": Missed!";
            rechargeCount -= 2;
            return calcDamage(target, true, false);
        }

        string bossAbility() {
            // really simplistic calculation that doesn't take into account if boss hp/max changes
            int change = getStat(0) - hp - damageTaken;
            damageTaken = getStat(0) - hp;
            if (change <= 0) return name + ": Waiting for a chance to counter.";
            setStatAdd(static_cast<int>(change * .03), 1);
            return name + ": Getting angry.";
        }

        string basicAttack(Fruit* target) override {
            if (!checkIfHit(target)) return name + ": Missed!";
            string returnThis = "";
            if(checkIfAdditionRecharge()) returnThis += name + ": Obtained another SKILL POINT!\n";
            returnThis += Fruit::basicAttack(target) + '\n';

            target->addEffect(statusMgr.getStatus(308));
            return returnThis + name + ": Wounded " + target->getName() + ".";
        }
};