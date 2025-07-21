#pragma once
#include "Player.h"
#include "Item.h"
#include <string>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;

class Shop {
 private:
  
  const unsigned MAX_NUM_ITEMS_IN_SHOP = 6;
  unsigned itemsInShop;
  string shopFile;
  string itemsFile = "assets/lists/ItemList.txt";
  vector<Item*> allItems;
  vector<Item*> itemsForSale;

 public:
  Shop(const string& pathToItemsList);
  ~Shop();
  string purchaseItem(Player* player, int itemIndex);
  void resetShop();
  void saveShop();
  int getItemPrice(unsigned index);
  void resetShopSave();

 private:
  void populateShop();
  int getRandomNumber(int max) const;  // Generates a random integer in [1, max]. 

  // max is the size of the container being passed in, not the maximum index.
  int getRandomIndex(int max) const;  // Generates a random integer in [0, max - 1]. 
};