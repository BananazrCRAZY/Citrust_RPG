#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/SuspenseScreen.hpp"
#include "include/TutorialScreen1.hpp"
#include <iostream>

using namespace std;

SuspenseScreen::SuspenseScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , nextButton("Graphics/nextButton.png", {1350,750}, 0.8)
{
    Image backgroundImage = LoadImage("Graphics/SuspenseScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

SuspenseScreen::~SuspenseScreen() {
    UnloadTexture(background);
}

void SuspenseScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (nextButton.isPressed(mousePos, mouseClicked)) {
        manager.ChangeScreen(make_unique<TutorialScreen1>(manager, exitGame));
    }
}

void SuspenseScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();
}