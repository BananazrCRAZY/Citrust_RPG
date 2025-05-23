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
        int specialAttack(Fruit*);
        void levelUp();
        bool useItem(Fruit*, int);
        void printItems();
        void savePlayer();
        void removeItem(unsigned);
        void addItem(unsigned);
};