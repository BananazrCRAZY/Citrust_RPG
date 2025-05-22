#include "../include/ConsumableItem.h"

ConsumableItem::ConsumableItem(
  string name,
  string description,
  int cost = 0,
  int cooldown = 1,
  Status* effect,
  double appearanceProbability = 0.15,
  int remainingUses = 1
) : Item(name, description, cost, cooldown, effect, appearanceProbability), remainingUses(remainingUses) { }

int ConsumableItem::getRemainingUses() const { return remainingUses; }