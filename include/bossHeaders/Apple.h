#pragma once
#include "Boss.h"

class Apple : public Boss {
    public:
        Apple(string, string);
        int specialAttack(Fruit*);
        int bossAttack();
};