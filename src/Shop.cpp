#include "include/Objects/Shop.h"
#include "include/Objects/Player.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include <cassert>

using std::ifstream;
using std::ofstream;
using std::cerr;
using std::endl;
using std::string;

Shop::Shop(const string& file) : itemsInShop(0), shopFile(file), shopEnd(nullptr), itemsForSale(new Item*[MAX_NUM_ITEMS_IN_SHOP]) {
  ifstream iFile(shopFile);
  if(!iFile.good()) {
    cerr << "Error: Shop.cpp, Shop(), iFile not good" << endl;
    exit(1);
  }
  json data;
  iFile >> data;

  bool inShop = true;
  for (auto& it : data) {
    int id = it["id"];
    if (id == 0) {
      inShop = false;
      shopEnd = new Item(0, "Shop End", "", 0, 0, 0, 0, 0, "");
      continue;
    }
    string name = it.value("name", "Error name");

    string desc = it.value("description", "");
    int cost = it.value("cost", 0);
    bool consumable = it.value("consumable", 0) != 0;
    int cooldownDefault = it.value("cooldownDefault", 0);
    int appearanceProb = it.value("appearanceProbability", 0);
    bool useOnPlayer = it.value("useOnPlayer", 0) != 0;
    string iconPath = it.value("iconPath", "");

    if (inShop) {
      itemsForSale[itemsInShop] = new Item(
        id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath
      );
      itemsInShop++;
    } else allItems.push_back(new Item(
        id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath
      ));
  }

  for(unsigned i = itemsInShop; i < MAX_NUM_ITEMS_IN_SHOP; i++) itemsForSale[i] = nullptr;
  iFile.close();
}

Shop::~Shop() {
  for (Item* item : allItems) delete item;
  for (unsigned i = 0; i < itemsInShop; i++) delete itemsForSale[itemsInShop];
  delete shopEnd;
}

string Shop::purchaseItem(Player* player, unsigned itemIndex) {
  if (itemIndex >= itemsInShop) {
    cerr << "Error: purchaseItem itemIndex is out of range" << endl;
    exit(1);
  }
  player->newItem(itemsForSale[itemIndex]);
  string returnLine = "You bought " + itemsForSale[itemIndex]->getName() + "!";
  itemsForSale[itemIndex] = nullptr;
  return returnLine;
}

int Shop::getItemPrice(unsigned index) {
  if (index >= itemsInShop) {
    cerr << "Error: getItemPrice itemIndex is out of range" << endl;
    exit(1);
  }
  if (itemsForSale[index] == nullptr) return -1;
  return itemsForSale[index]->getCost();
}

void Shop::populateShop() {
  assert(itemsInShop == 0);  // Shop must be empty beforehand

  if (allItems.size() < MAX_NUM_ITEMS_IN_SHOP) {  // if there are less than 6 items left to buy
    for (unsigned i = 0; i < allItems.size(); i++) {
      itemsForSale[i] = allItems.at(i);
      itemsInShop++;
    }
    allItems.clear();
    for (unsigned i = itemsInShop - 1; i < MAX_NUM_ITEMS_IN_SHOP; i++) {
      itemsForSale[i] = nullptr;
    }
  } else {
    while (itemsInShop != MAX_NUM_ITEMS_IN_SHOP) {
      int randomIndex = getRandomIndex(allItems.size());
      Item* selectedItem = allItems.at(randomIndex);  // Select a random item from allItems
      if (getRandomNumber(100) <= selectedItem->getAppearanceProbabiity()) {  // RNG to see if that selected item makes it in the shop
        itemsForSale[itemsInShop] = allItems.at(randomIndex);
        allItems.erase(allItems.begin()+randomIndex);
        itemsInShop++;
      }
    }
  }
}

void Shop::returnItems() {
  for (unsigned i = 0; i < itemsInShop; i++) {
    if (itemsForSale[i] != nullptr) allItems.push_back(itemsForSale[i]);
  }
  itemsInShop = 0;
}

void Shop::resetShop() {
  returnItems();
  populateShop();
}

void Shop::saveShop() {
  ofstream oFile(shopFile);
  if (!oFile.good()) {
    cerr << "Error: opening file, saveShop" << std::endl;
    exit(1);
  }

  json data = json::array();

  for (unsigned i = 0; i < itemsInShop; i++) {
    Item* item = itemsForSale[i];
    if (item == nullptr) continue;

    json obj;
    obj["id"] = item->getId();
    obj["name"] = item->getName();
    obj["description"] = item->getDescription();
    obj["cost"] = item->getCost();
    obj["consumable"] = item->isConsumableTrue() ? 1 : 0;
    obj["cooldownDefault"] = item->getCooldownDefault();
    obj["appearanceProbability"] = item->getAppearanceProbabiity();
    obj["useOnPlayer"] = item->isUseOnPlayer() ? 1 : 0;
    obj["iconPath"] = item->getIcon();

    data.push_back(obj);
  }

  if (shopEnd != nullptr) {
    json endMarker;
    endMarker["id"] = shopEnd->getId();
    endMarker["name"] = shopEnd->getName();
    data.push_back(endMarker);
  }

  for (Item* item : allItems) {
    json obj;
    obj["id"] = item->getId();
    obj["name"] = item->getName();
    obj["description"] = item->getDescription();
    obj["cost"] = item->getCost();
    obj["consumable"] = item->isConsumableTrue() ? 1 : 0;
    obj["cooldownDefault"] = item->getCooldownDefault();
    obj["appearanceProbability"] = item->getAppearanceProbabiity();
    obj["useOnPlayer"] = item->isUseOnPlayer() ? 1 : 0;
    obj["iconPath"] = item->getIcon();

    data.push_back(obj);
  }

  oFile << data.dump(2);
  oFile.close();
}

void Shop::resetShopSave() {
  ifstream iFile("assets/lists/items.json");
  if (!iFile.good()) {
    cerr << "Error: opening original items list, resetShopSave" << std::endl;
    exit(1);
  }
  ofstream oFile(shopFile);
  if (!oFile.good()) {
    cerr << "Error: opening shop file, resetShopSave" << std::endl;
    exit(1);
  }

  string output = "";
  while(iFile >> output) oFile << output << '\n';

  iFile.close();
  oFile.close();
}

int Shop::getRandomIndex(int max) const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, max-1);
  int random_number = dist(gen);

  return random_number;
}

int Shop::getRandomNumber(int max) const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, max);
  int random_number = dist(gen);

  return random_number;
}
