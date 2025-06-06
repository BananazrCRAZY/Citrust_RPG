#include "include/TutorialScreen.hpp"
#include "include/TitleScreen.hpp"
#include "include/NameScreen.hpp"
#include "include/AppleBossScreen.hpp"
#include <iostream>

using namespace std;

TutorialScreen::TutorialScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
{
    Image backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen1.png");
    
    switch (manager.GetTutorialCount()) {
            case 1:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen2.png");
                break;
            case 2:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen3.png");
                break;
            case 3:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen4.png");
                break;
            case 4:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen5.png");
                break;
            case 5:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen6.png");
                break;
            case 6:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen7.png");
                break;
            case 7:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen8.png");
                break;
            case 8:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen9.png");
                break;
            case 9:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen10.png");
                break;
            case 10:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen11.png");
                break;
            case 11:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen12.png");
                break;
            case 12:
                backgroundImage = LoadImage("Graphics/TutorialScreens/TutorialScreen13.png");
                break;
    }

    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

TutorialScreen::~TutorialScreen() {
    UnloadTexture(background);
}

void TutorialScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (IsKeyPressed(KEY_SPACE)) {
        if (manager.GetTutorialCount() == 12) {
            manager.setInput(5);
            manager.ChangeScreen(make_unique<AppleBossScreen>(manager, exitGame));
        } else {
            manager.AddTutorialCount(1);
            manager.ChangeScreen(make_unique<TutorialScreen>(manager, exitGame));
        }
    }
}

void TutorialScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
}