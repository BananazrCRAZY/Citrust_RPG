#include "include/LoadScreen.hpp"
#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include <iostream>

using namespace std;

LoadScreen::LoadScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , saveButton1("Graphics/saveButton1.png", {650,300}, 0.8)
    , saveButton2("Graphics/saveButton2.png", {650,435}, 0.8)
    , saveButton3("Graphics/saveButton3.png", {650,576}, 0.8)
    , backButton("Graphics/backButton.png", {1350,750}, 0.8)
{
    Image backgroundImage = LoadImage("Graphics/LoadScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

LoadScreen::~LoadScreen() {
    UnloadTexture(background);
}

void LoadScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (saveButton1.isPressed(mousePos, mouseClicked)) {
        manager.setInput(2);
    }
    if (saveButton2.isPressed(mousePos, mouseClicked)) {
        manager.setInput(3);
    }
    if (saveButton3.isPressed(mousePos, mouseClicked)) {
        manager.setInput(4);
    }
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.ChangeScreen(make_unique<TitleScreen>(manager, exitGame));
    }
}

void LoadScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    saveButton1.Draw();
    saveButton2.Draw();
    saveButton3.Draw();
    backButton.Draw();
}