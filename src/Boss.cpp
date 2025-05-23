#include "Boss.h"
#include <string>
#include <fstream>
#include <iostream>

using std::cerr;
using std::string;

Boss::Boss(string mainFile, string itemF) : Fruit(mainFile), itemFile(itemF) {
    std::ifstream iFile(itemFile);
    if (!iFile.good()) {
        cerr << "Error with file fstream" << std::endl;
        exit(1);
    }

    // need to finish when item implemented
}

int Boss::endOfTurn() {

}