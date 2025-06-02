#pragma once
#include "Player.h"
#include "Item.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Shop {
 private:
  const unsigned MAX_NUM_ITEMS_IN_SHOP = 6;
  unsigned itemsInShop;
  string itemsFile;
  vector<Item*> allItems;
  vector<Item*> itemsForSale;

 public:
  Shop(string& pathToItemsList);
  int purchaseItem(Fruit* player, int itemIndex);
  void resetShop();
  void saveShop();

 private:
  void populateShop();
  int getRandomNumber(int max) const;  // Generates a random integer in [1, max]
};