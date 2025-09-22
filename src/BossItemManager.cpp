#include "include/Objects/BossItemManager.h"

#include "include/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;
using std::ifstream;


BossItemManager::BossItemManager(StatusManager& statusMgr) {
    ifstream iFile("assets/lists/boss_items.json");
    if(!iFile.good()) {
        std::cerr << "Error: BossItemManager.cpp, BossItemManager(), iFile !good\n";
        exit(1);
    }
    json data;
    iFile >> data;

    unsigned i = 0;
    for (auto& it : data) {
        int id = it["id"];
        string name = it.value("name", "Error name");
        string desc = it.value("description", "");
        int cost = it.value("cost", 0);
        bool consumable = it.value("consumable", 0) != 0;
        int cooldownDefault = it.value("cooldownDefault", 0);
        int appearanceProb = it.value("appearanceProbability", 0);
        bool useOnPlayer = it.value("useOnPlayer", 0) != 0;
        string iconPath = it.value("iconPath", "");

        items[i++] = new Item(statusMgr, id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath);
    }
    iFile.close();
}

BossItemManager::~BossItemManager() {
    for (unsigned i = recentItem+1; i < 8; i++) delete items[i];
}

Item* BossItemManager::getBossItem(unsigned index) {
    recentItem = index;
    return items[index];
}