#pragma once
#include <string>
#include "Status.h"
#include "Fruit.h"

using std::string;

class Item {
 private:
  string filePath;
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
  ~Item();
  void use(Fruit* target);
  void decreaseCooldown();

  // Getters
  string getFilePath() const { return filePath; }
  string getName() const;
  string getDescription() const;
  int getCost() const;
  int getCooldown() const;
  double getAppearanceProbabiity() const;
  bool isConsumableTrue() const;
  Status* getStatus() const { return effect; }
};