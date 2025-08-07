#include "include/ShopScreen.hpp"
#include "include/BuyItemPopup.hpp"
#include <iostream>

using namespace std;

ShopScreen::ShopScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , item1(manager.getShopItem(0)->getIcon().c_str(), {285,300}, 332, 195)
    , item2(manager.getShopItem(1)->getIcon().c_str(), {635,300}, 332, 195)
    , item3(manager.getShopItem(2)->getIcon().c_str(), {982,300}, 332, 195)
    , item4(manager.getShopItem(3)->getIcon().c_str(), {285,520}, 332, 195)
    , item5(manager.getShopItem(4)->getIcon().c_str(), {635,520}, 332, 195)
    , item6(manager.getShopItem(5)->getIcon().c_str(), {982,520}, 332, 195)
    , backButton("Graphics/backButton.png", {50,750}, 0.8)
{
    Image backgroundImage = LoadImage("Graphics/ShopScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

}

ShopScreen::~ShopScreen() {
    UnloadTexture(background);
}

void ShopScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (item1.isPressed(mousePos, mouseClicked)) {
        cout << "item1 pressed\n";
       // add popup here
    }
    if (item2.isPressed(mousePos, mouseClicked)) {
        cout << "item2 pressed\n";
    }
    if (item3.isPressed(mousePos, mouseClicked)) {
        cout << "item3 pressed\n";
    }
    if (item4.isPressed(mousePos, mouseClicked)) {
        cout << "item4 pressed\n";
    }
    if (item5.isPressed(mousePos, mouseClicked)) {
        cout << "item5 pressed\n";
    }
    if (item6.isPressed(mousePos, mouseClicked)) {
        cout << "item6 pressed\n";
    }
    
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
    }
}

void ShopScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);

    // need to draw items
    item1.Draw();
    item2.Draw();
    item3.Draw();
    item4.Draw();
    item5.Draw();
    item6.Draw();
    backButton.Draw();
}