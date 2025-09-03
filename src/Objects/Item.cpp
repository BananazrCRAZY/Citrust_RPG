#include "include/Objects/Item.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::cerr;

Item::Item(const string& file) : filePath(file), cooldown(0) {
  ifstream iFile(file);
  if (!iFile.good()) {
    cerr << "Error with item file fstream" << std::endl;
    exit(1);
  }

  getline(iFile, name);
  getline(iFile, description);
  iFile >> cost;
  iFile >> isConsumable;
  iFile >> cooldownDefault;
  iFile >> appearanceProbability;
  string statusFile;
  iFile >> statusFile;
  if (!iFile.good()) {
    cerr << "Error: Item file format fstream at status file" << std::endl;
    exit(1);
  }
  effect = new Status(statusFile);
  
  iFile >> useOnPlayer;
  iFile >> iconPath;
  if (!iFile.good()) {
    cerr << "Error: Item file format fstream" << std::endl;
    exit(1);
  }
  iFile.close();
}

Item::~Item() {
  delete effect;
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

bool Item::isConsumableTrue() const { return isConsumable; }
