#include "Item.h"

Item::Item(
    string name,
    string description,
    int cost,
    int uses,
    int cooldown,
    Status* effect,
    double appearanceProbability,
    bool isConsumable
) :
  name(name),
  description(description),
  cost(cost),
  uses(uses),
  cooldownDefault(cooldown),
  cooldown(0),
  effect(effect),
  appearanceProbability(appearanceProbability),
  isConsumable(isConsumable) { }

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

bool Item::isConsumableTrue() const { return isConsumable; }
