#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen1.hpp"
#include "include/TutorialScreen2.hpp"
#include <iostream>

using namespace std;

TutorialScreen1::TutorialScreen1(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen1.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen1::~TutorialScreen1() {
    UnloadTexture(background);
}

void TutorialScreen1::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen2>(manager, exitGame));
    }
}

void TutorialScreen1::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}