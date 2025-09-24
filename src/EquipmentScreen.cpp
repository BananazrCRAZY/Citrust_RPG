#include "include/Screens/EquipmentScreen.hpp"
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
    , statsButton("Graphics/Buttons/statsButton.png", {75, 350}, .8)
    , statsMenu({800, 75}, {500, 750}, {805, 80}, .5, "Graphics/Buttons/xCloseButton.png", manager.getBoss(), manager.getPlayer(), false)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/EquippingScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

    float xPos = 465;
    for (unsigned i = 0; i < 6; i++) {
        if (i < p->getNumberBattleItems()) equipped[i] = new InventoryButton(p->getBattleItem(i)->getIcon().c_str(), {xPos, 135}, itemWidth, itemHeight, RED);
        else {
            equipped[i] = new InventoryButton("Graphics/blank.png", {xPos, 135}, itemWidth, itemHeight, RED);
            equipped[i]->disableButton();
        }
        xPos += 155;
    }

    for (unsigned i = 0; i < player->getNumberInventoryItems(); i++) {
        int row = i / maxPerRow;
        int col = i % maxPerRow;

        float xPos = unequippedXStart + col * unequippedSpacingX;
        float yPos = 320 + row * unequippedSpacingY;

        unequipped[i] = new InventoryButton(p->getInventoryItem(i)->getIcon().c_str(), {xPos, yPos}, itemWidth, itemHeight, WHITE);

        unequippedSize++;
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
    mainPopup.Update();
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
        return;
    }

    if (statsButton.isPressed(mousePos, mouseClicked)) statsMenu.toggleVisible();

    if (statsMenu.isVisible()) {
        statsMenu.Update(mousePos, mouseClicked, manager);
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

                    float xPos = unequippedXStart;
                    float yPos = 320;
                    if (unequippedSize != 0) {
                        yPos = unequipped[unequippedSize-1]->getButtonYPos();
                        if (unequipped[unequippedSize-1]->getButtonXPos() >= 1300) yPos += unequippedSpacingY;
                        else xPos = unequipped[unequippedSize-1]->getButtonXPos() + unequippedSpacingX;
                    }

                    unequipped[unequippedSize]->setBackingColor(WHITE);
                    unequipped[unequippedSize]->setButtonXPos(xPos);
                    unequipped[unequippedSize]->setButtonYPos(yPos);
                    equipped[5] = new InventoryButton("Graphics/blank.png", {1240, 135}, itemWidth, itemHeight, RED);
                    equipped[5]->disableButton();
                    unequippedSize++;
                } else {  // for equipping an item
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

    // equipped item buttons press check
    for (unsigned i = 0; i < 6; i++) {
        if (equipped[i]->isPressed(mousePos, mouseClicked)) {
            equipMenu.setEquipped(true);
            equipMenu.showItem(i);
            return;
        }
    }

    // unequipped item buttons press check
    for (unsigned i = 0; i < unequippedSize; i++) {
        // Only check if mouse is inside the visible panel
        if (CheckCollisionPointRec(mousePos, scrollPanel)) {
            if (unequipped[i]->isPressed(mousePos, mouseClicked)) {
                equipMenu.setEquipped(false);
                equipMenu.showItem(i);
                return;
            }
        }
    }

    // Scroll only when mouse is inside the unequipped panel
    if (CheckCollisionPointRec(mousePos, scrollPanel)) {
        scrollOffset += GetMouseWheelMove() * 30.0f; // scroll speed
    }

    // compute total rows
    int totalRows = (unequippedSize + maxPerRow - 1) / maxPerRow;
    float maxScroll = totalRows * unequippedSpacingY - maxVisibleRows * unequippedSpacingY;
    if (maxScroll < 0) maxScroll = 0;

    // clamp
    if (scrollOffset > 0) scrollOffset = 0;
    if (scrollOffset < -maxScroll) scrollOffset = -maxScroll;

}

void EquipmentScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    statsButton.Draw();

    for (unsigned i = 0; i < 6; i++) equipped[i]->Draw();

    // Clip unequipped items to panel
    BeginScissorMode(unequippedXStart, 320, maxPerRow * unequippedSpacingX, maxVisibleRows * unequippedSpacingY - 75);

    for (unsigned i = 0; i < unequippedSize; i++) {
        // offset by scroll
        unequipped[i]->setButtonYPos(320 + (i / maxPerRow) * unequippedSpacingY + scrollOffset);
        unequipped[i]->setButtonXPos(unequippedXStart + (i % maxPerRow) * unequippedSpacingX);

        unequipped[i]->Draw();
    }

    EndScissorMode();

    statsMenu.Draw();
    equipMenu.Draw();
    backButton.Draw();
    mainPopup.Draw();
}