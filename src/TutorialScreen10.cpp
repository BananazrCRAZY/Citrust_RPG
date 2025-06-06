#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen10.hpp"
#include "include/TutorialScreen11.hpp"
#include <iostream>

using namespace std;

TutorialScreen10::TutorialScreen10(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen10.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen10::~TutorialScreen10() {
    UnloadTexture(background);
}

void TutorialScreen10::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen11>(manager, exitGame));
    }
}

void TutorialScreen10::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}