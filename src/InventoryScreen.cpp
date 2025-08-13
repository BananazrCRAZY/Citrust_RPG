#include "include/AppleBossScreen.hpp"
#include "include/InventoryScreen.hpp"
#include <iostream>

using namespace std;

InventoryScreen::InventoryScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , item1("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    , item2("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    , item3("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , item4("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    , item5("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    , item6("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , backButton("Graphics/Buttons/backButton.png", {1350,750}, 0.8)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/InventoryScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

InventoryScreen::~InventoryScreen() {
    UnloadTexture(background);
}

void InventoryScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before in boss fight
    }

    if(item1.isPressed(mousePos, mouseClicked)) {
        manager.setInput(2);
        manager.PopScreen();
    }
    if(item2.isPressed(mousePos, mouseClicked)) {
        manager.setInput(3);
        manager.PopScreen();
    }
    if(item3.isPressed(mousePos, mouseClicked)) {
        manager.setInput(4);
        manager.PopScreen();
    }
    if(item4.isPressed(mousePos, mouseClicked)) {
        manager.setInput(5);
        manager.PopScreen();
    }
    if(item5.isPressed(mousePos, mouseClicked)) {
        manager.setInput(6);
        manager.PopScreen();
    }
    if(item6.isPressed(mousePos, mouseClicked)) {
        manager.setInput(7);
        manager.PopScreen();
    }
}

void InventoryScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    // need to draw items
    backButton.Draw();
}