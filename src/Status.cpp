#include "include/Objects/Status.h"
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::cerr;

Status::Status(int id, string name, string desc, int dTurns, bool percent,
  int hp, int maxHp, int atk, int def, int arts, int res, int critR, int critD, int recharge, int turnChange,
  int evasion, int intellect, int basicDmg, int skillDmg, int dmgAmp, int weakness, int vuln, bool delThis) :
  id(id), name(name), description(desc), defaultTurns(dTurns), percentBased(percent), hpChange(hp), maxHpChange(maxHp),
  attackChange(atk), defenseChange(def), artsChange(arts), resChange(res), critRateChange(critR), critDamageChange(critD),
  rechargeCountChange(recharge), turnChange(turnChange), evasionChange(evasion), intellectChange(intellect),
  basicDmgChange(basicDmg), skillDmgChange(skillDmg), dmgAmpChange(dmgAmp), weaknessChange(weakness),
  vulnerabilityChange(vuln), deleteThisStatus(delThis), turns(defaultTurns)
{}

Status::Status(const Status& effect) :
  id(effect.getId()), name(effect.getName()), description(effect.getDescription()), defaultTurns(effect.getDefaultTurns()),
  percentBased(effect.isPercentBased()), hpChange(effect.getHpChange()), maxHpChange(effect.getMaxHpChange()),
  attackChange(effect.getAttackChange()), defenseChange(effect.getDefenseChange()), artsChange(effect.getArtsChange()),
  resChange(effect.getResChange()), critRateChange(effect.getCritRateChange()), critDamageChange(effect.getCritDamageChange()),
  rechargeCountChange(effect.getRechargeCountChange()), turnChange(effect.getTurnChange()), evasionChange(effect.getEvasionChange()),
  intellectChange(effect.getIntellectChange()), basicDmgChange(effect.getBasicDmgChange()), skillDmgChange(effect.getSkillDmgChange()),
  dmgAmpChange(effect.getDmgAmpChange()), weaknessChange(effect.getWeaknessChange()),
  vulnerabilityChange(effect.getVulnerabilityChange()), deleteThisStatus(effect.isDeleteThisStatus())
{}

void Status::decreaseTurn() { --turns; }

void Status::resetStatusTurns() { turns = defaultTurns; }
