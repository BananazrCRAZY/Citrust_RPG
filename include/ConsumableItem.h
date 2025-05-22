#include "Item.h"

class ConsumableItem : private Item {
 private:
  int remainingUses;
 
 public:
  ConsumableItem(
    string name,
    string description,
    int cost = 0,
    int cooldown = 1,
    Status* effect,
    double appearanceProbability = 0.15,
    int remainingUses = 1
  );
  
  int getRemainingUses() const;
};