#include "include/Screens/AppleBossScreen.hpp"
#include "include/Screens/InventoryScreen.hpp"
#include <iostream>

using namespace std;

InventoryScreen::InventoryScreen(ScreenManager& mgr, bool& exitFlag, Player* p)
    : manager(mgr)
    , exitGame(exitFlag)
    , player(p)
    , backButton("Graphics/Buttons/backButton.png", {1350,750}, 0.8)
    , menu({400, 100}, {800, 700}, {500, 600}, .7, "Graphics/Buttons/cancelButton.png", 0, manager, p)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/InventoryScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

    int xStart = 285;
    int xSpacing = 350;
    int yStart = 300;
    int ySpacing = 220;
    int buttonWidth = 332;
    int buttonHeight = 195;
    for (unsigned i = 0; i < player->getNumberBattleItems(); i++) {
        int xPos = xStart + xSpacing * (i % 3);
        int yPos = yStart + ySpacing * (i / 3);
        buttons[i] = new SolidButton(player->getBattleItem(i)->getIcon().c_str(), {(float)xPos, (float)yPos}, buttonWidth, buttonHeight);
    }
    for (unsigned i = player->getNumberBattleItems(); i < 6; i++) buttons[i] = nullptr;
}

InventoryScreen::~InventoryScreen() {
    UnloadTexture(background);
    for (unsigned i = 0; i < player->getNumberBattleItems(); i++) delete buttons[i];
}

void InventoryScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (manager.isPopup()) manager.getPopup()->Update();
    
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        return;
    }

    if (menu.isVisible()) {
        menu.Update(mousePos, mouseClicked);
        return;
    }

    for (unsigned i = 0; i < player->getNumberBattleItems(); i++) {
        if (buttons[i]->isPressed(mousePos, mouseClicked))  {
            menu.showItem(i);
            return;
        }
    }
}

void InventoryScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    for (unsigned i = 0; i < player->getNumberBattleItems(); i++) buttons[i]->Draw();
    if (menu.isVisible()) menu.Draw();
    backButton.Draw();

    if (manager.isPopup()) manager.getPopup()->Draw();
}