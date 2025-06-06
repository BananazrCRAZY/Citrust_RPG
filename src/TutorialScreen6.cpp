#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen6.hpp"
#include "include/TutorialScreen7.hpp"
#include <iostream>

using namespace std;

TutorialScreen6::TutorialScreen6(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen6.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen6::~TutorialScreen6() {
    UnloadTexture(background);
}

void TutorialScreen6::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        manager.ChangeScreen(make_unique<TutorialScreen7>(manager, exitGame));
    }
}

void TutorialScreen6::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}