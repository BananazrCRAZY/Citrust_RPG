#pragma once
#include <string>
#include "Status.h"
#include "StatusManager.h"
#include "Fruit.h"

using std::string;

class Item {
 private:
  int id;
  string name;
  string description;
  int cost;
  bool consumable;
  int cooldownDefault;
  int appearanceProbability;
  bool useOnPlayer;
  string iconPath;

  int cooldown;
  Status* effect;

 public:
  Item(StatusManager& statusMgr, int id, string name, string description, int cost, bool consumable, int cooldownDefault, int appearanceProb, bool useOnPlayer, string iconPath);
  void use(Fruit* target);
  void decreaseCooldown();
  void resetCooldown();

  int getId() const { return id; }
  string getName() const;
  string getDescription() const;
  int getCost() const;
  int getCooldown() const;
  int getCooldownDefault() const;
  double getAppearanceProbabiity() const;
  int getTurnsLast() const { return effect->getDefaultTurns(); }
  Status* getStatus() const { return effect; }
  string getIcon() const { return iconPath; }
  bool isConsumableTrue() const;
  bool isUseOnPlayer() const { return useOnPlayer; }
};