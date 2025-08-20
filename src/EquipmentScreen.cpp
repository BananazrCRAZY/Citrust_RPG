#include "include/EquipmentScreen.hpp"
#include <iostream>

using namespace std;

EquipmentScreen::EquipmentScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , item1("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    , item2("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    , item3("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , item4("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    , item5("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    , item6("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , backButton("Graphics/Buttons/backButton.png", {50,750}, 0.8)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/EquippingScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

EquipmentScreen::~EquipmentScreen() {
    UnloadTexture(background);
}

void EquipmentScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
    }
}

void EquipmentScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    // need to draw items
    backButton.Draw();
}