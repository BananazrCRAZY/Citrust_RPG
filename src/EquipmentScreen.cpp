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
            equipped[i] = new InventoryButton("Graphics/blank.png", {xPos, 175}, 100, 100, RED);
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

    for (unsigned i = 0; i < 6; i++) delete equipped[i];
    delete[] equipped;
    equipped = nullptr;

    for (unsigned i = 0; i < unequippedSize; i++) delete unequipped[i];
    delete[] unequipped;
    unequipped = nullptr;
}

void EquipmentScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
        return;
    }

    if (equipMenu.isVisible()) {
        equipMenu.Update(mousePos, mouseClicked);
        // updates the item icons on screen if an item is un/equipped
        if (!equipMenu.isVisible()) {
            if (manager.getInput() > 7) {
                if (equipMenu.isEquipped()) {  // for unequipping an item
                    unequipped[unequippedSize] = equipped[equipMenu.getIndex()];
                    float previousXPos = equipped[equipMenu.getIndex()]->getButtonXPos();
                    float setX;
                    for (unsigned i = equipMenu.getIndex(); i < 5; i++) {
                        setX = previousXPos;
                        previousXPos = equipped[i+1]->getButtonXPos();
                        equipped[i] = equipped[i+1];
                        equipped[i]->setButtonXPos(setX);
                    }

                    float xPos = 200;
                    float yPos = 400;
                    if (unequippedSize != 0) {
                        yPos = unequipped[unequippedSize-1]->getButtonYPos();
                        if (unequipped[unequippedSize-1]->getButtonXPos() >= 1400) yPos += 200;
                        else xPos = unequipped[unequippedSize-1]->getButtonXPos() + 135;
                    }

                    unequipped[unequippedSize]->setBackingColor(WHITE);
                    unequipped[unequippedSize]->setButtonXPos(xPos);
                    unequipped[unequippedSize]->setButtonYPos(yPos);
                    equipped[5] = new InventoryButton("Graphics/blank.png", {1125, 175}, 100, 100, RED);
                    equipped[5]->disableButton();
                    unequippedSize++;
                } else {
                    InventoryButton* equippedItem = unequipped[equipMenu.getIndex()];
                    float previousX = unequipped[equipMenu.getIndex()]->getButtonXPos();
                    float previousY = unequipped[equipMenu.getIndex()]->getButtonYPos();
                    float setX, setY;
                    for (unsigned i = equipMenu.getIndex(); i < player->getNumberInventoryItems()-1; i++) {
                        setX = previousX;
                        setY = previousY;
                        previousX = unequipped[i+1]->getButtonXPos();
                        previousY = unequipped[i+1]->getButtonYPos();
                        unequipped[i] = unequipped[i+1];
                        unequipped[i]->setButtonXPos(setX);
                        unequipped[i]->setButtonYPos(setY);
                    }

                    unsigned equipIndex = player->getNumberBattleItems();
                    equippedItem->setButtonXPos(equipped[equipIndex]->getButtonXPos());
                    equippedItem->setButtonYPos(equipped[equipIndex]->getButtonYPos());
                    equippedItem->setBackingColor(RED);
                    equipped[equipIndex] = equippedItem;

                    unequippedSize--;
                }
            }
        }
        return;
    }

    // equipped item buttons
    for (unsigned i = 0; i < 6; i++) {
        if (equipped[i]->isPressed(mousePos, mouseClicked)) {
            equipMenu.setEquipped(true);
            equipMenu.showItem(i);
            return;
        }
    }

    for (unsigned i = 0; i < unequippedSize; i++) {
        if (unequipped[i]->isPressed(mousePos, mouseClicked)) {
            equipMenu.setEquipped(false);
            equipMenu.showItem(i);
            return;
        }
    }
}

void EquipmentScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    // need to draw items
    for (unsigned i = 0; i < 6; i++) equipped[i]->Draw();
    for (unsigned i = 0; i < unequippedSize; i++) unequipped[i]->Draw();
    if (equipMenu.isVisible()) equipMenu.Draw();
    backButton.Draw();
}