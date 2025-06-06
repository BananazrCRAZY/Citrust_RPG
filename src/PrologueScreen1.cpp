#include "include/NameScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/TitleScreen.hpp"
#include "include/PrologueScreen1.hpp"
#include "include/PrologueScreen2.hpp"
#include <iostream>

using namespace std;

PrologueScreen1::PrologueScreen1 (ScreenManager& mgr, bool& exitFlag) : manager(mgr), exitGame(exitFlag), nextButton("Graphics/nextButton.png",{1200,680}, 1.6)
{

    Image backgroundImage = LoadImage("Graphics/PrologueScreen1.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

PrologueScreen1::~PrologueScreen1() {
    UnloadTexture(background);
}

void PrologueScreen1::Update(const Vector2& mousePos, bool mouseClicked) {

    if (nextButton.isPressed(mousePos, mouseClicked)) {
        cout <<  "Prologue Next entered: " <<  endl;
        manager.ChangeScreen(make_unique<PrologueScreen2>(manager, exitGame));
    }
}

void PrologueScreen1::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();

    string userName = manager.GetPlayerName();
    DrawText(userName.c_str(), 430, 471, 55, BLACK);
}