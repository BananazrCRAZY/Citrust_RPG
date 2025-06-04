#include "include/GameScreen.hpp"

GameScreen::GameScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    // Load game resources here
}

GameScreen::~GameScreen() {
    // Unload game resources here
}

void GameScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    // Your gameplay input & state updates
    // e.g. if you wanted to go back to TitleScreen:
    // if (someCondition) manager.ChangeScreen(...);
}

void GameScreen::Draw() {
    ClearBackground(RAYWHITE);
}
