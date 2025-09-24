#pragma once
#include "BossItemManager.h"
#include "Fruit.h"
#include "Item.h"
#include "Shop.h"
#include "StatusManager.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Shop;  // forward declartion

class Player : public Fruit {
    const int MAX_INVENTORY_SPACE = 6;
    Item* equippedEnd;
    vector<Item*> items;
    vector<Item*> battleItems;
    string inventoryList;
    void clearStats();
    void reAddStats();
    void checkIfCanEquipItem();

    public:
        Player(const string&, const string&, Shop*, BossItemManager&);
        ~Player();
        Player(const Player&) = delete;
        Player& operator=(const Player&) = delete;
        string specialAttack(Fruit*);
        string useItem(Fruit*, unsigned);
        void savePlayer();
        void unequipItem(unsigned);
        void equipItem(unsigned);
        void setName(const string& newName) { name = newName; }
        unsigned getNumberBattleItems() const { return battleItems.size(); }
        Item* getBattleItem(int i) const { return battleItems.at(i); }
        unsigned getNumberInventoryItems() const { return items.size(); }
        Item* getInventoryItem(int i) const { return items.at(i); }
        void newItem(Item* item);
        void levelUp();
        void endOfBattle();
        void endOfTurn();
        void resetPlayerSave();
};