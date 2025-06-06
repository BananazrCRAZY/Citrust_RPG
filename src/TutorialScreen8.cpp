#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen8.hpp"
#include "include/TutorialScreen9.hpp"
#include <iostream>

using namespace std;

TutorialScreen8::TutorialScreen8(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen8.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen8::~TutorialScreen8() {
    UnloadTexture(background);
}

void TutorialScreen8::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen9>(manager, exitGame));
    }
}

void TutorialScreen8::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}