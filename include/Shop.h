#pragma once
#include "Player.h"
#include "Item.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

class Shop {
 private:
  string itemsFile;
  vector<Item> allItems;
  vector<Item> itemsForSale;

 public:
  void purchaseItem(Fruit* player, int itemIndex);
  void resetShop();
  void saveShop();

 private:
  void loadAllItems();
};