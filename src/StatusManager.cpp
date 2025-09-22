#include "include/Objects/StatusManager.h"

#include "include/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using std::cerr;
using std::ifstream;

StatusManager::StatusManager() {
    ifstream iFile("assets/lists/statuses.json");
    if(!iFile.good()) {
        cerr << "Error: StatusManager.cpp, StatusManager(), iFile !good\n";
        exit(1);
    }
    json data;
    iFile >> data;

    for (auto& it : data) {
        int id = it["id"];
        string name = it.value("name", "Error name");
        string desc = it.value("description", "");
        int defaultTurns = it.value("defaultTurns", 0);
        bool percentBased = it.value("percentBased", 0) != 0;
        int hpChange = it.value("hpChange", 0);
        int maxHpChange = it.value("maxHpChange", 0);
        int attackChange = it.value("attackChange", 0);
        int defenseChange = it.value("defenseChange", 0);
        int artsChange = it.value("artsChange", 0);
        int resChange = it.value("resChange", 0);
        int critRateChange = it.value("critRateChange", 0);
        int critDmgChange = it.value("critDmgChange", 0);
        int rechargeCountChange = it.value("rechargeCountChange", 0);
        int turnChange = it.value("turnChange", 0);
        int evasionChange = it.value("evasionChange", 0);
        int intellectChange = it.value("intellectChange", 0);
        int basicDmgChange = it.value("basicDmgChange", 0);
        int skillDmgChange = it.value("skillDmgChange", 0);
        int dmgAmpChange = it.value("dmgAmpChange", 0);
        int weaknessChange = it.value("weaknessChange", 0);
        int vulnerabilityChange = it.value("vulnerabilityChange", 0);
        bool deleteThisStatus = it.value("deteleThisStatus", 0) != 0;

        effects.push_back(new Status(id, name, desc, defaultTurns, percentBased, hpChange, maxHpChange, attackChange, defenseChange,
            artsChange, resChange, critRateChange, critDmgChange, rechargeCountChange, turnChange, evasionChange, intellectChange,
            basicDmgChange, skillDmgChange, dmgAmpChange, weaknessChange, vulnerabilityChange, deleteThisStatus
        ));
    }
    iFile.close();
}

StatusManager::~StatusManager() {
    for (Status* status : effects) delete status;
    for (Status* status : deleteThisEffects) delete status;
}

const Status* StatusManager::getStatus(int id) {
    if (effects.back()->getId() < id) {
        cerr << "Error: StatusManager, getStatus(), id too large\n";
        exit(1);
    }
    return getStatusSearch(id, 0, effects.size()-1);
}

const Status* StatusManager::getStatusSearch(int id, unsigned lower, unsigned upper) {
    if (lower > upper) {
        cerr << "Error: StatusManager.cpp, getStatusSearch(), cannot find id: " << id << '\n';
        exit(1);
    }
    unsigned middle = lower + (upper-lower) / 2;
    int middleId = effects.at(middle)->getId();
    if (id == middleId) {
        if (effects.at(middle)->isDeleteThisStatus()) {
            deleteThisEffects.push_back(new Status(*effects.at(middle)));
            return deleteThisEffects.back();
        } else return effects.at(middle);
    } else if (id < middleId) return getStatusSearch(id, lower, middle-1);
    else return getStatusSearch(id, middle+1, upper);
}