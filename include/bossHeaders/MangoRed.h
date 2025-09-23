#pragma once
#include "Boss.h"

using std::to_string;

class MangoRed : public Boss {
    public:
        MangoRed(const string& main, int required, int proxy, StatusManager& statusMgr) : Boss(main, required, proxy, statusMgr) {
            hp = getStat(0) / 2;
        }
        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            string returnStr = calcDamage(target, false, false);
            target->setStatAdd(-30, 1);
            return returnStr + name + ": Decreased " + target->getName() + "'s ATK.";
        }

        // rage ability
        string bossAbility() {
            if (hp < (getStat(0) / 2)) {
                setStatAdd(75, 1);
                return name + ": ATK increased.";
            }
            return "";
        }
};