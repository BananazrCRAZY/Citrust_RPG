#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen3.hpp"
#include "include/TutorialScreen4.hpp"
#include <iostream>

using namespace std;

TutorialScreen3::TutorialScreen3(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen3.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen3::~TutorialScreen3() {
    UnloadTexture(background);
}

void TutorialScreen3::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen4>(manager, exitGame));
    }
}

void TutorialScreen3::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}