#include "../include/Status.h"

Status::Status(
  string name,
  string description,
  int defaultTurns = 1,
  bool percentBased = false,
  int turns = 0,
  double hpChange = 0.0,
  double maxHpChange = 0.0,
  double attackChange = 0.0,
  double defenseChange = 0,
  double artsChange = 0.0,
  double resChange = 0.0,
  double critRateChange = 0.0,
  double critDamageChange = 0.0,
  int rechargeCountChange = 0,
  int turnChange = 0,
  bool isBossStatus = false
) : name(name), 
  description(description), 
  defaultTurns(defaultTurns), 
  percentBased(percentBased), 
  turns(0), 
  hpChange(hpChange), 
  maxHpChange(maxHpChange), 
  attackChange(attackChange), 
  defenseChange(defenseChange), 
  artsChange(artsChange), 
  resChange(resChange), 
  critRateChange(critRateChange), 
  critDamageChange(critDamageChange), 
  rechargeCountChange(rechargeCountChange), 
  turnChange(turnChange),
  isBossStatus(isBossStatus) { }

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