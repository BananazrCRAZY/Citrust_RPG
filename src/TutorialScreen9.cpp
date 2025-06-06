#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen9.hpp"
#include "include/TutorialScreen10.hpp"
#include <iostream>

using namespace std;

TutorialScreen9::TutorialScreen9(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen9.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen9::~TutorialScreen9() {
    UnloadTexture(background);
}

void TutorialScreen9::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen10>(manager, exitGame));
    }
}

void TutorialScreen9::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}