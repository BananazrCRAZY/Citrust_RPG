#include "include/Objects/Item.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::cerr;

Item::Item(int id, string name, string decription, int cost, bool consumable, int cooldownDefault, int appearanceProb, bool useOnPlayer, string iconPath) :
  id(id),
  name(name),
  description(description),
  cost(cost),
  consumable(consumable),
  cooldownDefault(cooldownDefault),
  appearanceProbability(appearanceProb),
  useOnPlayer(useOnPlayer),
  iconPath(iconPath),
  cooldown(0),
  effect(nullptr)
{
  // search for status
}

string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
int Item::getCost() const { return cost; }
int Item::getCooldown() const { return cooldown; }
int Item::getCooldownDefault() const { return cooldownDefault; }
double Item::getAppearanceProbabiity() const { return appearanceProbability; }

void Item::use(Fruit* target) {
  target->addEffect(effect);
  cooldown = cooldownDefault;
}

void Item::decreaseCooldown() {
  cooldown--;
}

void Item::resetCooldown() { cooldown = 0; }

bool Item::isConsumableTrue() const { return consumable; }
