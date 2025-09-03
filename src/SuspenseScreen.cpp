#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/GameScreen.hpp"
#include "include/Screens/NameScreen.hpp"
#include "include/Screens/SuspenseScreen.hpp"
#include "include/Screens/TutorialScreen.hpp"
#include <iostream>

using namespace std;

SuspenseScreen::SuspenseScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , nextButton("Graphics/Buttons/nextButton.png", {1200,680}, 1.6)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/SuspenseScreen.png");
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
        manager.ChangeScreen(make_unique<TutorialScreen>(manager, exitGame));
    }
}

void SuspenseScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();
}