#pragma once
#include "Item.h"

class BossItemManager {
    Item* items[8];
    unsigned recentItem;

    public:
        BossItemManager();
        ~BossItemManager();
        BossItemManager(const BossItemManager&) = delete;
        BossItemManager& operator=(const BossItemManager&) = delete;
        Item* getBossItem(unsigned);
};