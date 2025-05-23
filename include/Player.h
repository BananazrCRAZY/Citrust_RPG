#pragma once
#include "Fruit.h"
//#include "Item.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Player : public Fruit {
    // vector<Item*> items;
    // vector<Item*> battleItems;

    public:
        Player(string file);
        int specialAttack(Fruit*);
        void levelUp();
        bool useItem(Fruit*, int);
        int endOfTurn();
        void savePlayer();
};