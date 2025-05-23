#include "../include/Item.h"

Item::Item(
    string name,
    string description,
    int cost = 0,
    int cooldown = 1,
    Status* effect,
    double appearanceProbability = 0.15
  ) :
  name(name), description(description), cost(cost), cooldown(cooldown), effect(effect), appearanceProbability(appearanceProbability) { }

string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
int Item::getCost() const { return cost; }
int Item::getCooldown() const { return cooldown; }
double Item::getAppearanceProbabiity() const { return appearanceProbability; }

void Item::use(Fruit& target) {
  target.addEffect(effect);
}

void Item::changeCooldown(int change) {
  this->cooldown += change;
}

int Item::getRemainingUses() const { return remainingUses; }
