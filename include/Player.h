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

    public:
        Player(string file);
        int specialAttack(Fruit*);
        void levelUp();
        bool useItem(Fruit*, int);
        void printItems();
        int endOfTurn();
        void savePlayer();
};