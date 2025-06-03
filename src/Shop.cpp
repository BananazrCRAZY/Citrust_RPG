#include "Shop.h"
#include "Player.h"
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

Shop::Shop(const string& pathToItemsList) : itemsFile(pathToItemsList){
  ifstream iFile(pathToItemsList);
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
  if(itemIndex > itemsForSale.size()-1 || itemIndex < 0) {
    cerr << "Error: purchaseItem itemIndex is out of range" << endl;
    exit(1);
  }
  player->newItem(itemsForSale.at(itemIndex));
  return "You bought " + itemsForSale.at(itemIndex)->getName() + "!";
}
int Shop::getItemPrice(unsigned index) {
  if (index > itemsForSale.size()-1) {
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
      shownItems.insert(selectedItem->getFilePath());
    }
  }
}

void Shop::resetShop() {
  itemsForSale.clear();
  itemsInShop = itemsForSale.size();  // Should be 0!
  populateShop();
}

void Shop::saveShop() {
  ifstream originalList("assets/listOfItems.txt");
  if (!originalList.is_open()) {
    cerr << "Couldn't open master item list file." << std::endl;
    exit(1);
  }

  ofstream unseenFile("assets/saves/Save1/Shop.txt", std::ios::trunc);  // std::ios::trunc clears the file after opening it
  if (!unseenFile.is_open()) {
    cerr << "Couldn't open or create unseen items save file." << std::endl;
    exit(1);
  }

  string line;
  while (std::getline(originalList, line)) {
    if (shownItems.find(line) == shownItems.end()) {  // If the line is NOT in the set (if the iterator from find() is not the end)
      unseenFile << line << '\n';
    }
  }

  unseenFile.close();
  originalList.close();
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
