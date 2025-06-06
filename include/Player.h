#pragma once
#include "Fruit.h"
#include "Item.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player : public Fruit {
    vector<Item*> items;
    vector<Item*> battleItems;
    string inventoryList;
    void levelUp();
    void clearStats();
    void reAddStats();

    public:
        Player(const string&, const string&);
        ~Player();
        string specialAttack(Fruit*);
        string useItem(Fruit*, unsigned);
        void savePlayer();
        void unequipItem(unsigned);
        void equipItem(unsigned);
        void setName(const string& newName) { name = newName; }
        Item* getBattleItem(int i) const { return battleItems.at(i); }
        Item* getInventoryItem(int i) const { return items.at(i); }
        void newItem(Item* item) { items.push_back(item); }
        void endOfBattle();
};