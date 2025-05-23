#include "Boss.h"
#include "Item.h"
#include "Status.h"
#include <string>
#include <fstream>
#include <iostream>

using std::cerr;
using std::string;
using std::ifstream;

Boss::Boss(string mainFile, string itemF) : Fruit(mainFile), itemDrop(new Item(itemF)) {}

int Boss::specialAttack(Fruit* target) {
    int damage = attackTotal * 2;
    if (checkIfCrit()) damage = damage * (critDmgTotal/100 + 1);
    damage  = damage - target->getDefense();
    if (damage <= 0) return 0;
    target->setHp(-1*damage);
    return damage;
}

int Boss::endOfTurn() {

}