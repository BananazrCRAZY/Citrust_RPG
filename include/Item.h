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
  bool useOnPlayer;
  string iconPath;

 public:
  Item(const string&);
  ~Item();
  void use(Fruit* target);
  void decreaseCooldown();
  void resetCooldown();

  string getFilePath() const { return filePath; }
  string getName() const;
  string getDescription() const;
  int getCost() const;
  int getCooldown() const;
  int getCooldownDefault() const;
  double getAppearanceProbabiity() const;
  Status* getStatus() const { return effect; }
  string getIcon() const { return iconPath; }
  bool isConsumableTrue() const;
  bool isUseOnPlayer() const { return useOnPlayer; }
};