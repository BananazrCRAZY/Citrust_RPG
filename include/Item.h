#pragma once
#include <string>
#include "Status.h"

using std::string;

class Item {
 private:
  string name;
  string description;
  int cost;
  int cooldown;
  Status* effect;
  double appearanceProbability;
  int remainingUses;

 public:
  Item(
    string name,
    string description,
    int cost = 0,
    int cooldown = 1,
    Status* effect,
    double appearanceProbability = 0.15
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
};