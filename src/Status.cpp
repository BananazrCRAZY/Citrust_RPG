#include "Status.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::cerr;

Status::Status(string file) {
  ifstream iFile(file);
  if (!iFile.good()) {
    cerr << "Error with file fstream" << std::endl;
    exit(1);
  }

  getline(iFile, name);
  getline(iFile, description);
  iFile >> defaultTurns;
  iFile >> percentBased;
  iFile >> hpChange;
  iFile >> maxHpChange;
  iFile >> attackChange;
  iFile >> defenseChange;
  iFile >> artsChange;
  iFile >> resChange;
  iFile >> critRateChange;
  iFile >> critDamageChange;
  iFile >> rechargeCountChange;
  iFile >> turnChange;
  if (!iFile.good()) {
    cerr << "Error with file fstream" << std::endl;
    exit(1);
  }
  iFile.close();
}

void Status::decreaseTurn() { if (turns > 0) --turns; }

void Status::resetStatus() { turns = defaultTurns; }

string Status::getName() const { return name; }
string Status::getDescription() const { return description; }
int Status::getDefaultTurns() const { return defaultTurns; }
int Status::getTurns() const { return turns; }
double Status::getHpChange() const { return hpChange; }
double Status::getMaxHpChange() const { return maxHpChange; }
double Status::getAttackChange() const { return attackChange; }
double Status::getDefenseChange() const { return defenseChange; }
double Status::getArtsChange() const { return artsChange; }
double Status::getResChange() const { return resChange; }
double Status::getCritRateChange() const { return critRateChange; }
double Status::getCritDamageChange() const { return critDamageChange; }
int Status::getRechargeCountChange() const { return rechargeCountChange; }
int Status::getTurnChange() const { return turnChange; }
bool Status::isBossStatusTF() const { return isBossStatus; }