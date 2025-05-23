#pragma once
#include <string>

using std::string;

class Status {
 private:
  string name;
  string description;
  int defaultTurns;
  int turns;
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
  Status(
    string name,
    string description,
    int defaultTurns = 1,
    int turns = 1,
    double hpChange = 0.0,
    double maxHpChange = 0.0,
    double attackChange = 0.0,
    double artsChange = 0.0,
    double resChange = 0.0,
    double critRateChange = 0.0,
    double critDamageChange = 0.0,
    int rechargeCountChange = 0,
    int turnChange = 0
  );

  void decreaseTurn();
  void resetStatus();

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
  bool isBossStatus() const;
};