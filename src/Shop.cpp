#include "include/Shop.h"
#include "include/Player.h"
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

Shop::Shop(const string& pathToItemsList) : itemsFile(pathToItemsList), itemsInShop(0) {
  ifstream iFile(itemsFile);
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

string Shop::purchaseItem(Player* player, int itemIndex) {
  if(itemIndex > (itemsForSale.size()-1) || itemIndex < 0) {
    cerr << "Error: purchaseItem itemIndex is out of range" << endl;
    exit(1);
  }
  player->newItem(itemsForSale.at(itemIndex));
  string returnLine = "You bought " + itemsForSale.at(itemIndex)->getName() + "!";
  itemsForSale.at(itemIndex) = nullptr;
  return returnLine;
}

int Shop::getItemPrice(unsigned index) {
  if (index > (itemsForSale.size()-1)) {
    cerr << "Error: getItemPrice itemIndex is out of range" << endl;
    exit(1);
  }
  return itemsForSale.at(index)->getCost();
}

void Shop::populateShop() {
  assert(itemsInShop == 0);  // Shop must be empty beforehand
  while (itemsInShop != 6) {
    int randomIndex = getRandomIndex(allItems.size());
    Item* selectedItem = allItems.at(randomIndex);  // Select a random item from allItems
    if (getRandomNumber(100) <= selectedItem->getAppearanceProbabiity()) {  // RNG to see if that selected item makes it in the shop
      itemsForSale.push_back(selectedItem);
      allItems.erase(allItems.begin()+randomIndex);
      itemsInShop++;
    }
  }
}

void Shop::resetShop() {
  itemsForSale.clear();
  itemsInShop = itemsForSale.size();  // Should be 0!
  populateShop();
}

void Shop::saveShop() {
  for (int i = 0; i < itemsInShop; i++) if (itemsForSale.at(i) != nullptr) allItems.push_back(itemsForSale.at(i));

  ofstream oFile(itemsFile);
  if (!oFile.good()) {
    cerr << "Couldn't open master item list file." << std::endl;
    exit(1);
  }

  for (int i = 0; i < allItems.size(); i++) {
    oFile << allItems.at(i)->getFilePath() << '\n';
  }
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
