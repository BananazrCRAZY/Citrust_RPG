#pragma once
#include "include/json.hpp"
#include "Player.h"
#include "Item.h"
#include "StatusManager.h"
#include <string>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector;
using json = nlohmann::json;

class Player;  // forward declaration for the player ptr

class Shop {
 private:
  
  const unsigned MAX_NUM_ITEMS_IN_SHOP = 6;
  unsigned itemsInShop;
  string shopFile = "assets/lists/items.json";
  string itemsInShopFile;
  vector<Item*> allItems;
  Item** itemsForSale;

 public:
  Shop(StatusManager& statusMgr, string inShop);
  ~Shop();
  string purchaseItem(Player* player, unsigned itemIndex);
  void resetShop();
  void returnItems();
  void saveShop();
  int getItemPrice(unsigned index);
  void resetShopSave();
  Item** getItemsForSale() { return itemsForSale; }
  Item* getItemById(int id);

 private:
  void populateShop();
  int getRandomNumber(int max) const;  // Generates a random integer in [1, max]. 

  // max is the size of the container being passed in, not the maximum index.
  int getRandomIndex(int max) const;  // Generates a random integer in [0, max - 1].

  Item* getItemById(int id, unsigned lower, unsigned upper);
};