#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/TutorialScreen13.hpp"
#include <iostream>

using namespace std;

TutorialScreen13::TutorialScreen13(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreen13.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen13::~TutorialScreen13() {
    UnloadTexture(background);
}

void TutorialScreen13::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        //manager.ChangeScreen(make_unique<TutorialScreen1>(manager, exitGame));
        cout << "tutorial done\n";
    }
}

void TutorialScreen13::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}