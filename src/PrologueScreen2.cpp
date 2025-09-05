#include "include/Screens/NameScreen.hpp"
#include "include/Screens/GameScreen.hpp"
#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/PrologueScreen1.hpp"
#include "include/Screens/PrologueScreen2.hpp"
#include "include/Screens/SuspenseScreen.hpp"
#include <iostream>

using namespace std;

PrologueScreen2::PrologueScreen2 (ScreenManager& mgr, bool& exitFlag) : manager(mgr), exitGame(exitFlag), nextButton("Graphics/Buttons/nextButton.png",{1260,720}, 1.4)
{

    Image backgroundImage = LoadImage("Graphics/GeneralScreens/PrologueScreen2.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

PrologueScreen2::~PrologueScreen2() {
    UnloadTexture(background);
}

void PrologueScreen2::Update(const Vector2& mousePos, bool mouseClicked) {

    if (nextButton.isPressed(mousePos, mouseClicked)) {
        //cout <<  "Prologue Next entered: " <<  endl;
        manager.ChangeScreen(make_unique<SuspenseScreen>(manager, exitGame));
    }
}

void PrologueScreen2::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();

    string userName = manager.GetPlayerName();
    DrawText(userName.c_str(), 810, 330, 55, BLACK);
}