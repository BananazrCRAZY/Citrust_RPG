#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/LoadScreen.hpp"
#include <iostream>

using namespace std;

TitleScreen::TitleScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , startButton("Graphics/newButton.png", {650,300}, 1)
    , loadButton("Graphics/loadButton.png", {650,450}, 1)
    , quitButton("Graphics/quitButton.png", {648,576}, 1)
{
    Image backgroundImage = LoadImage("Graphics/titleScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TitleScreen::~TitleScreen() {
    UnloadTexture(background);
}

void TitleScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (startButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(1);
    }
    if (loadButton.isPressed(mousePos, mouseClicked)) {
        manager.ChangeScreen(make_unique<LoadScreen>(manager, exitGame));
    }
    if (quitButton.isPressed(mousePos, mouseClicked)) {
        exitGame = true;
    }
}

void TitleScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    startButton.Draw();
    loadButton.Draw();
    quitButton.Draw();
}