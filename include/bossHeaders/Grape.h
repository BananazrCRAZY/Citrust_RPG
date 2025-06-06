#pragma once
#include "include/Boss.h"
#include "include/Status.h"
#include <vector>

using std::vector;
using std::to_string;

class Grape : public Boss {
    vector<Status*> effects = {
        new Status("assets/status/GrapeStatus/DecreaseArts.txt"),
        new Status("assets/status/GrapeStatus/DecreaseAttack.txt"),
        new Status("assets/status/GrapeStatus/DecreaseCritDmg.txt"),
        new Status("assets/status/GrapeStatus/DecreaseCritRate.txt"),
        new Status("assets/status/GrapeStatus/DecreaseDefense.txt"),
        new Status("assets/status/GrapeStatus/DecreaseRes.txt")
    };

    public:
        Grape(const string& main, const string& item, int required) : Boss(main, item, required) {}
        ~Grape() { for (unsigned i = 0; i < effects.size(); i++) delete effects.at(i); }
        string specialAttack(Fruit* target) {
            srand(time(0));
            string returnStatement = "";
            for (int i = 1; i < 4; i++) {
                int damage = arts->getTotal() * (1-(target->getRes()/100));
                target->setHp(-1 * damage);
                returnStatement += (name + ": Attack " + to_string(i) + " did " + to_string(damage) + " damage.\n");
                if ((rand() % 5) > 2) {
                    int effectIndex = rand() % effects.size();
                    target->addEffect(effects.at(effectIndex));
                    returnStatement += (name + ": Gave " + target->getName() + " " + effects.at(effectIndex)->getName() + ".");
                }
            }
            rechargeCount -= 2;
            return returnStatement;
        }

        string bossAbility() {
            bossAbilityCharge -= requiredBossCharge;
            turn++;
            return name + ": Charged up.";
        }
};