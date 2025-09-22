#pragma once
#include <string>

using std::string;

class Status {
 private:
  int id;
  string name;
  string description;
  int defaultTurns;
  bool percentBased;
  int hpChange;
  int maxHpChange;
  int attackChange;
  int defenseChange;
  int artsChange;
  int resChange;
  int critRateChange;
  int critDamageChange;
  int rechargeCountChange;
  int turnChange;
  int evasionChange;
  int intellectChange;
  int basicDmgChange;
  int skillDmgChange;
  int dmgAmpChange;
  int weaknessChange;
  int vulnerabilityChange;
  bool deleteThisStatus;

  int turns;

 public:
  Status(int id, string name, string desc, int dTurns, bool percent,
    int hp, int maxHp, int atk, int def, int arts, int res, int critR, int critD, int recharge, int turnChange,
    int evasion, int intellect, int basicDmg, int skillDmg, int dmgAmp, int weakness, int vuln, bool delThis
  );
  ~Status() = default;
  Status(const Status&);
  Status& operator=(const Status&) = delete;

  void decreaseTurn();
  void resetStatusTurns();

  // Getters
  int getId() const { return id; }
  string getName() const { return name; }
  string getDescription() const { return description; }
  int getDefaultTurns() const { return defaultTurns; }
  bool isPercentBased() const { return percentBased; }
  int getHpChange() const { return hpChange; }
  int getMaxHpChange() const { return maxHpChange; }
  int getAttackChange() const { return attackChange; }
  int getDefenseChange() const { return defenseChange; }
  int getArtsChange() const { return artsChange; }
  int getResChange() const { return resChange; }
  int getCritRateChange() const { return critRateChange; }
  int getCritDamageChange() const { return critDamageChange; }
  int getRechargeCountChange() const { return rechargeCountChange; }
  int getTurnChange() const { return turnChange; }
  int getEvasionChange() const { return evasionChange; }
  int getIntellectChange() const { return intellectChange; }
  int getBasicDmgChange() const { return basicDmgChange; }
  int getSkillDmgChange() const { return skillDmgChange; }
  int getDmgAmpChange() const { return dmgAmpChange; }
  int getWeaknessChange() const { return weaknessChange; }
  int getVulnerabilityChange() const { return vulnerabilityChange; }
  bool isDeleteThisStatus() const { return deleteThisStatus; }
  int getTurns() const { return turns; }
};