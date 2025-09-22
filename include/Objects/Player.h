#pragma once
#include "Fruit.h"
#include "Item.h"
#include "StatusManager.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player : public Fruit {
    Item* equippedEnd;
    vector<Item*> items;
    vector<Item*> battleItems;
    string inventoryList;
    void clearStats();
    void reAddStats();

    public:
        Player(const string&, const string&, StatusManager& statusMgr);
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
        void newItem(Item* item) { items.push_back(item); }
        void levelUp();
        void endOfBattle();
        void endOfTurn();
        void resetPlayerSave();
};