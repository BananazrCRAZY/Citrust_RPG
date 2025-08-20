#include "include/ShopScreen.hpp"
#include <iostream>

using namespace std;

ShopScreen::ShopScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , item1("", {285,300}, 332, 195)
    , item2("", {635,300}, 332, 195)
    , item3("", {982,300}, 332, 195)
    , item4("", {285,520}, 332, 195)
    , item5("", {635,520}, 332, 195)
    , item6("", {982,520}, 332, 195)
    , backButton("Graphics/Buttons/backButton.png", {50,750}, 0.8)
    , menu({400, 100}, {800, 700}, {500, 600}, .7, "Graphics/Buttons/cancelButton.png", 0, manager)
{
    if (manager.getShopItem(0) != nullptr) item1.setTexture(manager.getShopItem(0)->getIcon().c_str());
    else item1.disableButton();
    if (manager.getShopItem(1) != nullptr) item2.setTexture(manager.getShopItem(1)->getIcon().c_str());
    else item2.disableButton();
    if (manager.getShopItem(2) != nullptr) item3.setTexture(manager.getShopItem(2)->getIcon().c_str());
    else item3.disableButton();
    if (manager.getShopItem(3) != nullptr) item4.setTexture(manager.getShopItem(3)->getIcon().c_str());
    else item4.disableButton();
    if (manager.getShopItem(4) != nullptr) item5.setTexture(manager.getShopItem(4)->getIcon().c_str());
    else item5.disableButton();
    if (manager.getShopItem(5) != nullptr) item6.setTexture(manager.getShopItem(5)->getIcon().c_str());
    else item6.disableButton();

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
        return;
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
            cout << "exit shopscreen"; 
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
    string calCount = "Calories: " + to_string(manager.getCalories());
    DrawText(calCount.c_str(), 1300, 100, 35, BLACK);
}