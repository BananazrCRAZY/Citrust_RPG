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

Shop::Shop(const string& file) : itemsInShop(0), shopFile(file), itemsForSale(new Item*[MAX_NUM_ITEMS_IN_SHOP]) {
  ifstream iFile(shopFile);
  if(!iFile.good()) {
    cerr << "Error with the Shop file stream" << endl;
    exit(1);
  }

  string itemFile;
  while(getline(iFile, itemFile)) {
    Item* newItem = new Item(itemFile);
    allItems.push_back(newItem);
  }
}

Shop::~Shop() {
  for (Item* item : allItems) delete item;
}

string Shop::purchaseItem(Player* player, unsigned itemIndex) {
  if (itemIndex > (MAX_NUM_ITEMS_IN_SHOP-1)) {
    cerr << "Error: purchaseItem itemIndex is out of range" << endl;
    exit(1);
  }
  player->newItem(itemsForSale[itemIndex]);
  string returnLine = "You bought " + itemsForSale[itemIndex]->getName() + "!";
  itemsForSale[itemIndex] = nullptr;
  return returnLine;
}

int Shop::getItemPrice(unsigned index) {
  if (index > (MAX_NUM_ITEMS_IN_SHOP-1)) {
    cerr << "Error: getItemPrice itemIndex is out of range" << endl;
    exit(1);
  }
  if (itemsForSale[index] == nullptr) return -1;
  return itemsForSale[index]->getCost();
}

void Shop::populateShop() {
  assert(itemsInShop == 0);  // Shop must be empty beforehand

  if (allItems.size() < 6) {  // if there are less than 6 items left to buy
    for (unsigned i = 0; i < allItems.size(); i++) {
      itemsForSale[i] = allItems.at(i);
      itemsInShop++;
    }
    allItems.clear();
  } else {
    while (itemsInShop != 6) {
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

void Shop::resetShop() {
  itemsInShop = 0;
  populateShop();
}

void Shop::saveShop() {
  for (unsigned i = 0; i < MAX_NUM_ITEMS_IN_SHOP; i++) if (itemsForSale[i] != nullptr) allItems.push_back(itemsForSale[i]);

  ofstream oFile(shopFile);
  if (!oFile.good()) {
    cerr << "Error: opening file, saveShop" << std::endl;
    exit(1);
  }

  for (int i = 0; i < allItems.size(); i++) {
    oFile << allItems.at(i)->getFilePath() << '\n';
  }
  oFile.close();
}

void Shop::resetShopSave() {
  ifstream iFile("assets/lists/ItemList.txt");
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
