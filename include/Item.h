#pragma once
#include <string>
#include "Status.h"
#include "Fruit.h"

using std::string;

class Item {
 private:
  string file;
  string name;
  string description;
  int cost;
  int cooldownDefault;
  int cooldown;
  Status* effect;
  double appearanceProbability;
  bool isConsumable;

 public:
  Item(string);

  void use(Fruit* target);
  void changeCooldown(int change);

  // Getters
  string getFile() const { return file; }
  string getName() const;
  string getDescription() const;
  int getCost() const;
  int getCooldown() const;
  double getAppearanceProbabiity() const;
  bool isConsumableTrue() const;
  Status* getStatus() const { return effect; }
};