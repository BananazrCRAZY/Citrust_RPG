#include "include/Objects/Game.h"
#include <iostream>

int main() {
    // At the very beginning of main()
    ChangeDirectory(GetApplicationDirectory());

    Game* game = new Game();
    game->runGame();
    delete game;
}