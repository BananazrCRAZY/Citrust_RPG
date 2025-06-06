#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen2.hpp"
#include "include/TutorialScreen3.hpp"
#include <iostream>

using namespace std;

TutorialScreen2::TutorialScreen2(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen2.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen2::~TutorialScreen2() {
    UnloadTexture(background);
}

void TutorialScreen2::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen3>(manager, exitGame));
    }
}

void TutorialScreen2::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}