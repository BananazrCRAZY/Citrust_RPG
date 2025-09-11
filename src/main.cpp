#include "include/Objects/Game.h"
#include <iostream>

int main() {
    ChangeDirectory(GetApplicationDirectory());

    Game* game = new Game();
    game->runGame();
    delete game;
}