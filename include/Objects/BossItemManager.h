#pragma once
#include "Item.h"
#include "StatusManager.h"

class BossItemManager {
    Item* items[8];
    unsigned recentItem;

    public:
        BossItemManager(StatusManager&);
        ~BossItemManager();
        BossItemManager(const BossItemManager&) = delete;
        BossItemManager& operator=(const BossItemManager&) = delete;
        Item* getBossItem(unsigned);
};