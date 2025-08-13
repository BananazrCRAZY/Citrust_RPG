#include "include/ShopScreen.hpp"
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
    , backButton("Graphics/Buttons/backButton.png", {50,750}, 0.8)
    , menu({400, 100}, {800, 700}, {500, 600}, .7, "Graphics/Buttons/cancelButton.png", 0, manager)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/ShopScreen.png");
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
    if (backButton.isPressed(mousePos, mouseClicked)) {
        manager.PopScreen();
        //need to go back to same screen as before, the interlude
    }

    if (menu.isVisible()) {
        menu.Update(mousePos, mouseClicked);
        if (!menu.isVisible()) {
            goto inputCheck;
        }
        return;
    }

    if (item1.isPressed(mousePos, mouseClicked)) {
        menu.showItem(0);
    }
    if (item2.isPressed(mousePos, mouseClicked)) {
        menu.showItem(1);
    }
    if (item3.isPressed(mousePos, mouseClicked)) {
        menu.showItem(2);
    }
    if (item4.isPressed(mousePos, mouseClicked)) {
        menu.showItem(3);
    }
    if (item5.isPressed(mousePos, mouseClicked)) {
        menu.showItem(4);
    }
    if (item6.isPressed(mousePos, mouseClicked)) {
        menu.showItem(5);
    }
    return;

    inputCheck:
    switch (manager.getInput()) {
        case -1:
            return;
        case 1:
            item1.setTexture("");
            item1.disableButton();
            break;
        case 2:
            item2.setTexture("");
            item2.disableButton();
            break;
        case 3:
            item3.setTexture("");
            item3.disableButton();
            break;
        case 4:
            item4.setTexture("");
            item4.disableButton();
            break;
        case 5:
            item5.setTexture("");
            item5.disableButton();
            break;
        case 6:
            item6.setTexture("");
            item6.disableButton();
            break;
        default:
            exit(1);
    }
}

void ShopScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    // drawn in layers so menu needs to be bottom
    item1.Draw();
    item2.Draw();
    item3.Draw();
    item4.Draw();
    item5.Draw();
    item6.Draw();
    backButton.Draw();
    menu.Draw();
}