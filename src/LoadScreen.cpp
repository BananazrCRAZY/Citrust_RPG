#include "include/Screens/LoadScreen.hpp"
#include "include/Screens/TitleScreen.hpp"
#include "include/Screens/GameScreen.hpp"
#include "include/Screens/NameScreen.hpp"
#include <iostream>

using namespace std;

LoadScreen::LoadScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , saveButton1("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    , saveButton2("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    , saveButton3("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , trashButton("Graphics/Buttons/trashClosedIcon.png", {1130, 690}, .7)
    , backButton("Graphics/Buttons/backButton.png", {1350,750}, 0.8)
    , deleteSave(false)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/LoadScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

    trashBorder = {trashButton.getXPos(), trashButton.getYPos(), trashButton.getXSize(), trashButton.getYSize()};
}

LoadScreen::~LoadScreen() {
    UnloadTexture(background);
}

void LoadScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (saveButton1.isPressed(mousePos, mouseClicked)) {
        if (deleteSave) manager.setInput(5);
        else manager.setInput(2);
    }
    if (saveButton2.isPressed(mousePos, mouseClicked)) {
        if (deleteSave) manager.setInput(6);
        else manager.setInput(3);
    }
    if (saveButton3.isPressed(mousePos, mouseClicked)) {
        if (deleteSave) manager.setInput(7);
        else manager.setInput(4);
    }
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.ChangeScreen(make_unique<TitleScreen>(manager, exitGame));
    }

    if (trashButton.isPressed(mousePos, mouseClicked)) {
        trashBorder = {trashButton.getXPos(), trashButton.getYPos(), trashButton.getXSize(), trashButton.getYSize()};
        if (deleteSave) {
            trashButton.SetTexture("Graphics/Buttons/trashClosedIcon.png", .7);
            deleteSave = false;
        } else {
            trashButton.SetTexture("Graphics/Buttons/trashOpenIcon.png", .7);
            deleteSave = true;
        }
    }
}

void LoadScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    saveButton1.Draw();
    saveButton2.Draw();
    saveButton3.Draw();
    trashButton.Draw();
    DrawRectangleLinesEx(trashBorder, 3, DARKGRAY);
    backButton.Draw();
}