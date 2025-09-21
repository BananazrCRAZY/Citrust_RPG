#pragma once
#include "Item.h"

class BossItemManager {
    Item* items[8];

    public:
        BossItemManager();
        ~BossItemManager();
        Item* getBossItem(unsigned);
};