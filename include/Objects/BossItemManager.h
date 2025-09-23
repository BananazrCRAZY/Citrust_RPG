#pragma once
#include "Item.h"
#include "StatusManager.h"

class BossItemManager {
    StatusManager& statusMgr;
    Item* items[8];
    void addItems();
    void deleteItems();

    public:
        BossItemManager(StatusManager&);
        ~BossItemManager();
        BossItemManager(const BossItemManager&) = delete;
        BossItemManager& operator=(const BossItemManager&) = delete;
        Item* getBossItem(unsigned);
        void resetManager();
};