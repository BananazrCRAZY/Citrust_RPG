#include "Apple.h"

Apple::Apple(string boss, string item) : Boss(boss, item) {}

int Apple::specialAttack(Fruit* target) {
    Boss::specialAttack(target);
}

int Apple::bossAttack() {
    hp += 10;
    return -10;
}