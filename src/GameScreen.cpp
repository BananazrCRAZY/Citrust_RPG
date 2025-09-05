#include "include/Screens/GameScreen.hpp"
#include "include/Screens/TitleScreen.hpp"
#include <iostream>

using namespace std;

GameScreen::GameScreen(ScreenManager& mgr, bool& exitFlag, const string& savePath)
    : manager(mgr)
    , exitGame(exitFlag)
    , game(nullptr)
    , gameStarted(false)
{
    // Load game resources here
    game = new Game();

    game->openFile(savePath);
}

GameScreen::~GameScreen() {
    // Unload game resources here
    delete game;
}

void GameScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    // Your gameplay input & state updates
    // e.g. if you wanted to go back to TitleScreen:
    // if (someCondition) manager.ChangeScreen(...);
    if(!gameStarted) {
        //game->runGame();
        gameStarted = true;

        manager.ChangeScreen(make_unique<TitleScreen>(manager, exitGame));
        return;
    }
}

void GameScreen::Draw() {
    ClearBackground(RAYWHITE);
}
