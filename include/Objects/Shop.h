#pragma once
#include "include/json.hpp"
#include "Player.h"
#include "Item.h"
#include <string>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;
using json = nlohmann::json;

class Shop {
 private:
  
  const unsigned MAX_NUM_ITEMS_IN_SHOP = 6;
  unsigned itemsInShop;
  string shopFile;
  Item* shopEnd;
  vector<Item*> allItems;
  Item** itemsForSale;

 public:
  Shop(const string& pathToItemsList);
  ~Shop();
  string purchaseItem(Player* player, unsigned itemIndex);
  void resetShop();
  void returnItems();
  void saveShop();
  int getItemPrice(unsigned index);
  void resetShopSave();
  Item** getItemsForSale() { return itemsForSale; }

 private:
  void populateShop();
  int getRandomNumber(int max) const;  // Generates a random integer in [1, max]. 

  // max is the size of the container being passed in, not the maximum index.
  int getRandomIndex(int max) const;  // Generates a random integer in [0, max - 1]. 
};