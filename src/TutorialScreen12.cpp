#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen12.hpp"
#include "include/TutorialScreen13.hpp"
#include <iostream>

using namespace std;

TutorialScreen12::TutorialScreen12(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen12.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen12::~TutorialScreen12() {
    UnloadTexture(background);
}

void TutorialScreen12::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen13>(manager, exitGame));
    }
}

void TutorialScreen12::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}