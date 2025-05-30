#pragma once
#include "Fruit.h"
#include "Item.h"
#include "UI.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player : public Fruit {
    vector<Item*> items;
    vector<Item*> battleItems;
    UI ui;
    string inventoryList;

    public:
        Player(string, string);
        string specialAttack(Fruit*);
        void levelUp();
        string useItem(Fruit*, unsigned);
        void printItems();
        void savePlayer();
        void removeItem(unsigned);
        void addItem(unsigned);
        void setName(string newName) { name = newName; }
};