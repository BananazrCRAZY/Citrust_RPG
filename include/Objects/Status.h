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
  bool deleteThisStatus;

 public:
  Status(string);
  ~Status() = default;

  void decreaseTurn();
  void resetStatusTurns();

  // Getters
  string getName() const;
  string getDescription() const;
  int getDefaultTurns() const;
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
  bool isPercentBased() const { return percentBased; }
  bool isDeleteThisStatus() const { return deleteThisStatus; }
};