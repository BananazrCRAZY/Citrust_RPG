#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen7.hpp"
#include "include/TutorialScreen8.hpp"
#include <iostream>

using namespace std;

TutorialScreen7::TutorialScreen7(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen7.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen7::~TutorialScreen7() {
    UnloadTexture(background);
}

void TutorialScreen7::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen8>(manager, exitGame));
    }
}

void TutorialScreen7::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}