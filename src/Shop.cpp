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

Shop::Shop(StatusManager& statusMgr, string inShop) : itemsInShop(0), itemsInShopFile(inShop), itemsForSale(new Item*[MAX_NUM_ITEMS_IN_SHOP]) {
  ifstream iFile(shopFile);
  if(!iFile.good()) {
    cerr << "Error: Shop.cpp, Shop(), iFile opening shopFile" << endl;
    exit(1);
  }
  json data;
  iFile >> data;

  for (auto& it : data) {
    int id = it["id"];
    string name = it.value("name", "Error name");
    string desc = it.value("description", "");
    int cost = it.value("cost", 0);
    bool consumable = it.value("consumable", 0) != 0;
    int cooldownDefault = it.value("cooldownDefault", 0);
    int appearanceProb = it.value("appearanceProbability", 0);
    bool useOnPlayer = it.value("useOnPlayer", 0) != 0;
    string iconPath = it.value("iconPath", "");

    allItems.push_back(new Item(
      statusMgr, id, name, desc, cost, consumable, cooldownDefault, appearanceProb, useOnPlayer, iconPath
    ));
  }
  iFile.close();

  iFile.open(inShop);
  if(!iFile.good()) {
    cerr << "Error: Shop.cpp, Shop(), iFile opening inShop" << endl;
    exit(1);
  }

  int output;
  while (iFile >> output) {
    if (output == -1) itemsForSale[itemsInShop] = nullptr;
    else itemsForSale[itemsInShop] = getItemById(output);
    itemsInShop++;
  }
  if (itemsInShop > MAX_NUM_ITEMS_IN_SHOP) {
    cerr << "Error: Shop.cpp, Shop(), inShop contains too many item ids" << endl;
    exit(1);
  }
  iFile.close();
}

Shop::~Shop() {
  for (Item* item : allItems) delete item;
  for (unsigned i = 0; i < itemsInShop; i++) delete itemsForSale[i];
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
  ofstream oFile(itemsInShopFile);
  if (!oFile.good()) {
    cerr << "Error: Shop.cpp, saveShop(), opening itemsInShopFile" << std::endl;
    exit(1);
  }

  for (unsigned i = 0; i < itemsInShop; i++) {
    if (itemsForSale[i] == nullptr) oFile << "-1\n";
    else oFile << itemsForSale[i]->getId() << '\n';
  }

  oFile.close();
}

void Shop::resetShopSave() {
  ofstream oFile(itemsInShopFile);
  if (!oFile.good()) {
    cerr << "Error: Shop.cpp, resetShopSave(), oFile opening itemsInShopFile\n";
    exit(1);
  }

  for (unsigned i = 0; i < MAX_NUM_ITEMS_IN_SHOP; i++) oFile << "-1\n";
  
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

Item* Shop::getItemById(int id) {
    if (allItems.back()->getId() < id) {
        cerr << "Error: Shop.cpp, getItemById(), id too large\n";
        exit(1);
    }
    if (id == 0) return nullptr;
    return getItemById(id, 0, allItems.size()-1);
}

Item* Shop::getItemById(int id, unsigned lower, unsigned upper) {
    if (lower > upper) {
        cerr << "Error: Error: Shop.cpp, getItemById(), cannot find id: " << id << '\n';
        exit(1);
    }
    unsigned middle = lower + (upper-lower) / 2;
    int middleId = allItems.at(middle)->getId();
    if (id == middleId) {
        Item* holder = allItems.at(middle);
        allItems.erase(allItems.begin()+middle);
        return holder;
    } else if (id < middleId) return getItemById(id, lower, middle-1);
    else return getItemById(id, middle+1, upper);
}