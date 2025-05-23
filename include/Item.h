#pragma once
#include <string>
#include "Status.h"
#include "Fruit.h"

using std::string;

class Item {
 private:
  string name;
  string description;
  int cost;
  int uses;
  int cooldownDefault;
  int cooldown;
  Status* effect;
  double appearanceProbability;
  int remainingUses;
  bool isConsumable;

 public:
  Item(
    string name,
    string description,
    int cost = 0,
    int uses = 1,
    int cooldownDefault = 1,
    Status* effect,
    double appearanceProbability = 0.15,
    bool isConsumable = false
  );

  void use(Fruit& target);
  void changeCooldown(int change);

  // Getters

  string getName() const;
  string getDescription() const;
  int getCost() const;
  int getCooldown() const;
  double getAppearanceProbabiity() const;
  int getRemainingUses() const;
  bool isConsumableTrue() const;
};