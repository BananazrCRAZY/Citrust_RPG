#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen11.hpp"
#include "include/TutorialScreen12.hpp"
#include <iostream>

using namespace std;

TutorialScreen11::TutorialScreen11(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen11.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen11::~TutorialScreen11() {
    UnloadTexture(background);
}

void TutorialScreen11::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen12>(manager, exitGame));
    }
}

void TutorialScreen11::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}