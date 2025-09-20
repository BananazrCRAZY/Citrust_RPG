#pragma once
#include "Boss.h"
#include "include/Objects/Status.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::to_string;

class Grape : public Boss {
    string effects[6] = {
        "assets/status/GrapeStatus/DecreaseArts.txt",
        "assets/status/GrapeStatus/DecreaseAttack.txt",
        "assets/status/GrapeStatus/DecreaseCritDmg.txt",
        "assets/status/GrapeStatus/DecreaseCritRate.txt",
        "assets/status/GrapeStatus/DecreaseDefense.txt",
        "assets/status/GrapeStatus/DecreaseRes.txt"
    };

    public:
        Grape(const string& main, int required, const string& proxy) : Boss(main, required, proxy) {}

        string specialAttack(Fruit* target) {
            rechargeCount -= 2;
            string returnStatement = "";
            int damage = arts->getTotal() * (1-(target->getRes()/100.0));
            for (int i = 1; i < 4; i++) {
                target->setHp(-1 * damage);
                returnStatement += (name + ": Attack " + to_string(i) + " did " + to_string(damage) + " damage.\n");
                if ((rand() % 5) > 2) {
                    int effectIndex = rand() % 6;
                    target->addEffect(new Status(effects[effectIndex]));
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