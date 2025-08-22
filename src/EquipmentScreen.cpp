#include "include/EquipmentScreen.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

EquipmentScreen::EquipmentScreen(ScreenManager& mgr, bool& exitFlag, Player* p)
    : manager(mgr)
    , exitGame(exitFlag)
    , player(p)
    , equipped(new InventoryButton*[6])
    , unequipped(new InventoryButton*[50])
    , unequippedSize(0)
    // , item1("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    // , item2("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    // , item3("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    // , item4("Graphics/Buttons/saveButton1.png", {650,300}, 0.8)
    // , item5("Graphics/Buttons/saveButton2.png", {650,435}, 0.8)
    // , item6("Graphics/Buttons/saveButton3.png", {650,576}, 0.8)
    , backButton("Graphics/Buttons/backButton.png", {50,750}, 0.8)
    , equipMenu({400, 100}, {800, 700}, {500, 600}, .7, "Graphics/Buttons/cancelButton.png", 0, manager, p)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/EquippingScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

    float xPos = 450;
    for (unsigned i = 0; i < 6; i++) {
        if (i < p->getNumberBattleItems()) equipped[i] = new InventoryButton(p->getBattleItem(i)->getIcon().c_str(), {xPos, 175}, 100, 100, RED);
        else {
            equipped[i] = new InventoryButton("", {xPos, 175}, 100, 100, RED);
            equipped[i]->disableButton();
        }
        xPos += 135;
    }

    xPos = 200;
    for (unsigned i = 0; i < player->getNumberInventoryItems(); i++) {
        unequipped[i] = new InventoryButton(p->getInventoryItem(i)->getIcon().c_str(), {xPos, 400}, 100, 100, WHITE);
        unequippedSize++;
        xPos += 135;
    }
}

EquipmentScreen::~EquipmentScreen() {
    UnloadTexture(background);
}

void EquipmentScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
        return;
    }

    if (equipMenu.isVisible()) {
        equipMenu.Update(mousePos, mouseClicked);
        return;
    }

    // equipped item buttons
    for (unsigned i = 0; i < 6; i++) {
        if (equipped[i]->isPressed(mousePos, mouseClicked)) {
            equipMenu.showItem(i);
            return;
        }
    }

    for (unsigned i = 0; i < unequippedSize; i++) {
        if (unequipped[i]->isPressed(mousePos, mouseClicked)) {
            return;
        }
    }
}

void EquipmentScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    // need to draw items
    for (unsigned i = 0; i < 6; i++) equipped[i]->Draw();
    for (unsigned i = 0; i < unequippedSize; i++) unequipped[i]->Draw();
    backButton.Draw();
}