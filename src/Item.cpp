#include "Item.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::cerr;

Item::Item(string file) : filePath(file) {
  ifstream iFile(file);
  if (!iFile.good()) {
    cerr << "Error with file fstream" << std::endl;
    exit(1);
  }

  getline(iFile, name);
  getline(iFile, description);
  iFile >> cost;
  iFile >> isConsumable;
  iFile >> cooldownDefault;
  iFile >> appearanceProbability;
  string statusFile = "";
  iFile >> statusFile;
  effect = new Status(statusFile);
  if (!iFile.good()) {
    cerr << "Error with file fstream" << std::endl;
    exit(1);
  }
  iFile.close();
}

string Item::getName() const { return name; }
string Item::getDescription() const { return description; }
int Item::getCost() const { return cost; }
int Item::getCooldown() const { return cooldown; }
double Item::getAppearanceProbabiity() const { return appearanceProbability; }

void Item::use(Fruit* target) {
  target->addEffect(effect);
}

void Item::changeCooldown(int change) {
  this->cooldown += change;
}

bool Item::isConsumableTrue() const { return isConsumable; }
