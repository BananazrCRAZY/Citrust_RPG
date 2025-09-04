#include "include/Screens/NameScreen.hpp"
#include "include/Screens/GameScreen.hpp"
#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/PrologueScreen1.hpp"
#include "include/Screens/PrologueScreen2.hpp"
#include <iostream>

using namespace std;

PrologueScreen1::PrologueScreen1 (ScreenManager& mgr, bool& exitFlag) : manager(mgr), exitGame(exitFlag), nextButton("Graphics/Buttons/nextButton.png",{1200,680}, 1.6)
{

    Image backgroundImage = LoadImage("Graphics/GeneralScreens/PrologueScreen1.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
    cout <<  "\nPrologue created \n";
}

PrologueScreen1::~PrologueScreen1() {
    UnloadTexture(background);
}

void PrologueScreen1::Update(const Vector2& mousePos, bool mouseClicked) {

    if (nextButton.isPressed(mousePos, mouseClicked)) {
        cout <<  "\nPrologue Next entered: \n";
        manager.ChangeScreen(make_unique<PrologueScreen2>(manager, exitGame));
    }
}

void PrologueScreen1::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();

    string userName = manager.GetPlayerName();
    DrawText(userName.c_str(), 430, 471, 55, BLACK);
}