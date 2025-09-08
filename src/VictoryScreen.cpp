#include "include/Screens/VictoryScreen.hpp"
#include <iostream>

using namespace std;

VictoryScreen::VictoryScreen (ScreenManager& mgr, int cal) : 
    manager(mgr), 
    nextButton("Graphics/Buttons/nextButton.png",{1200,680}, 1.6),
    calories(cal)
{

    Image backgroundImage = LoadImage("Graphics/GeneralScreens/victoryScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

VictoryScreen::~VictoryScreen() {
    UnloadTexture(background);
}

void VictoryScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (nextButton.isPressed(mousePos, mouseClicked)) {
        // just gets out of victory screen loop in gameLoop()
        manager.setInput(0);
    }
}

void VictoryScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    string calText = "You Obtained " + to_string(calories) + " Calories!";
    int calTextWidth = MeasureText(calText.c_str(), 33);
    DrawText(calText.c_str(), 800 - calTextWidth/2, 710, 33, BLACK);
    nextButton.Draw();
}