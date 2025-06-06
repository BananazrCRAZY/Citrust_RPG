#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen4.hpp"
#include "include/TutorialScreen5.hpp"
#include <iostream>

using namespace std;

TutorialScreen4::TutorialScreen4(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen4.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen4::~TutorialScreen4() {
    UnloadTexture(background);
}

void TutorialScreen4::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen5>(manager, exitGame));
    }
}

void TutorialScreen4::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}