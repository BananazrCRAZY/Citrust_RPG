#include "include/Screens/ShopScreen.hpp"
#include <iostream>

using namespace std;

ShopScreen::ShopScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , backButton("Graphics/Buttons/backButton.png", {50,750}, 0.8)
    , refreshButton("Graphics/Buttons/refreshButton.png", {1400, 725}, .8)
    , menu({400, 100}, {800, 700}, {500, 600}, .7, "Graphics/Buttons/cancelButton.png", 0, manager)
{
    resetItems();

    Image backgroundImage = LoadImage("Graphics/GeneralScreens/ShopScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

ShopScreen::~ShopScreen() {
    UnloadTexture(background);
    for (unsigned i = 0; i < 6; i++) delete items[i];
}

void ShopScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    mainPopup.Update();
    
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
        return;
    }

    if (menu.isVisible()) {
        menu.Update(mousePos, mouseClicked);
        if (!menu.isVisible()) {
            goto inputCheck;
        }
        return;
    }

    if (refreshButton.isPressed(mousePos, mouseClicked)) {
        if (manager.getCalories() >= 50) {
            manager.getCaloriesVar() -= 50;
            manager.getShop()->resetShop();
            for (unsigned i = 0; i < 6; i++) delete items[i];
            resetItems();
            return;
        }
    }

    for (unsigned i = 0; i < 6; i++) {
        if (items[i]->isPressed(mousePos, mouseClicked)) menu.showItem(i);
    }

    return;

    inputCheck:
        switch (manager.getInput()) {
            case -1:
                return;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                if (manager.getCalories() >= manager.getShopItem(manager.getInput()-1)->getCost()) {
                    items[manager.getInput()-1]->setTexture("Graphics/Objects/soldOut.png");
                    items[manager.getInput()-1]->disableButton();
                }
                break;
            default:
                cerr << "error: exit shopscreen"; 
                exit(1);
        }
}

void ShopScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    // drawn in layers so menu needs to be bottom
    for (unsigned i = 0; i < 6; i++) items[i]->Draw();
    backButton.Draw();
    refreshButton.Draw();
    menu.Draw();
    string calCount = "Calories: " + to_string(manager.getCalories());
    DrawText(calCount.c_str(), 1300, 100, 35, BLACK);

    mainPopup.Draw();
}

void ShopScreen::resetItems() {
    int xStart = 285;
    int xSpacing = 350;
    int yStart = 300;
    int ySpacing = 220;
    int buttonWidth = 332;
    int buttonHeight = 195;
    for (unsigned i = 0; i < 6; i++) {
        int xPos = xStart + xSpacing * (i % 3);
        int yPos = yStart + ySpacing * (i / 3);
        if (manager.getShopItem(i) == nullptr) {
            items[i] = new SolidButton("Graphics/Objects/soldOut.png", {(float)xPos, (float)yPos}, buttonWidth, buttonHeight);
            items[i]->disableButton();
        } else items[i] = new SolidButton(manager.getShopItem(i)->getIcon().c_str(), {(float)xPos, (float)yPos}, buttonWidth, buttonHeight);
    }
}