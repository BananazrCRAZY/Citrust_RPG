#pragma once
#include <string>

using std::string;

class Status {
 private:
  string name;
  string description;
  int defaultTurns;
  int turns;
  bool percentBased;
  double hpChange;
  double maxHpChange;
  double attackChange;
  double defenseChange;
  double artsChange;
  double resChange;
  double critRateChange;
  double critDamageChange;
  int rechargeCountChange;
  int turnChange;
  bool isBossStatus;

 public:
  Status(string);

  void decreaseTurn();
  void resetStatus();

  // Getters
  string getName() const;
  string getDescription() const;
  int getTurns() const;
  double getHpChange() const;
  double getMaxHpChange() const;
  double getAttackChange() const;
  double getDefenseChange() const;
  double getArtsChange() const;
  double getResChange() const;
  double getCritRateChange() const;
  double getCritDamageChange() const;
  int getRechargeCountChange() const;
  int getTurnChange() const;
  bool isBossStatusTF() const;
  bool isPercentBased() const { return percentBased; }
};