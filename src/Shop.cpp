#include "Shop.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <random>
#include <cassert>

using std::ifstream;
using std::cerr;
using std::endl;
using std::string;

Shop::Shop(string& pathToItemsList) : itemsFile(pathToItemsList){
  ifstream iFile(pathToItemsList);
  if(!iFile.good()) {
    cerr << "Error with the file stream in Shop" << endl;
    exit(1);
  }

  string itemFile;
  while(iFile >> itemFile) {
    Item* newItem = new Item(itemFile);
    allItems.push_back(newItem);
  }
}

int Shop::purchaseItem(Fruit* player, int itemIndex) {
  player->newItem(itemsForSale.at(itemIndex));
  return itemsForSale.at(itemIndex)->getCost();
}

void Shop::populateShop() {
  assert(itemsInShop == 0);  // Shop must be empty beforehand
  while (itemsInShop != 6) {
    Item* selectedItem = allItems.at(getRandomNumber(allItems.size()));  // Select a random item from allItems
    if (getRandomNumber(100) <= selectedItem->getAppearanceProbabiity()) {  // RNG to see if that selected item makes it in the shop
      itemsForSale.push_back(selectedItem);
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
  // TODO
}

int Shop::getRandomNumber(int max) const {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, max);
  int random_number = dist(gen);

  return random_number;
}