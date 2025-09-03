#include "include/Screens/InterludeScreen.hpp"
#include "include/Screens/AppleBossScreen.hpp"
#include "include/Screens/ShopScreen.hpp"
#include "include/Screens/EquipmentScreen.hpp"

#include <iostream>

using namespace std;

InterludeScreen::InterludeScreen(ScreenManager& mgr, bool& exitFlag, Player* p)
    : manager(mgr)
    , exitGame(exitFlag)
    , player(p)
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
        manager.PushScreen(make_unique<EquipmentScreen>(manager, exitGame, player));
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