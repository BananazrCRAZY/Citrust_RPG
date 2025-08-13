#include "include/InterludeScreen.hpp"
#include "include/AppleBossScreen.hpp"
#include "include/ShopScreen.hpp"
#include "include/EquipmentScreen.hpp"

#include <iostream>

using namespace std;

InterludeScreen::InterludeScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , shopButton("Graphics/Buttons/shopButton.png", {600,350}, 0.7)
    , inventoryButton("Graphics/Buttons/circleInventoryButton.png", {850,350}, 0.7)
    , bossButton("Graphics/Buttons/bossButton.png", {725,480}, 0.7)
    , quitButton("Graphics/Buttons/quitButton.png", {30, 20}, 0.7)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/InterludeScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

InterludeScreen::~InterludeScreen() {
    UnloadTexture(background);
}

void InterludeScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (shopButton.isPressed(mousePos, mouseClicked)) {
        manager.PushScreen(make_unique<ShopScreen>(manager, exitGame));
    }
    if (inventoryButton.isPressed(mousePos, mouseClicked)) {
        manager.PushScreen(make_unique<EquipmentScreen>(manager, exitGame));
    }
    if (bossButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(7);
    }
    if (quitButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(0);
    }
}

void InterludeScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    shopButton.Draw();
    inventoryButton.Draw();
    bossButton.Draw();
    quitButton.Draw();
}