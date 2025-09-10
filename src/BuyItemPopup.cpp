#include "include/Popups/BuyItemPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

BuyItemPopup::BuyItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& sm) : 
    ItemPopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath, index, sm, "Graphics/Buttons/buyButton.png")
{}

void BuyItemPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    IndefinitePopup::Update(mousePos, mouseClicked);

    if (secondButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        manager.setInput(itemIndex+1);
    }
}

void BuyItemPopup::Draw() {
    if (!visible) return;
    ItemPopup::Draw();

    string name = manager.getShopItem(itemIndex)->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 30, 30, BLACK);

    if (needToUpdateDesc) {
        string message = manager.getShopItem(itemIndex)->getDescription();
        reshapeMsg(message, itemDesc, itemLines, 20);
    }
    for (unsigned i = 0; i < itemLines; i++) {
        int textWidthDesc = MeasureText(itemDesc[i].c_str(), 20);
        DrawText(itemDesc[i].c_str(), box.x + (box.width - textWidthDesc)/2, box.y + 340 + i * 23, 20, BLACK);
    }

    if (needToUpdateDesc) {
        string effectDescMsg = manager.getShopItem(itemIndex)->getStatus()->getName() 
            + ": " + manager.getShopItem(itemIndex)->getStatus()->getDescription();
        reshapeMsg(effectDescMsg, effectDesc, effectLines, 20);
        needToUpdateDesc = false;
    }
    for (unsigned i = 0; i < effectLines; i++) {
        int effectDescWidth = MeasureText(effectDesc[i].c_str(), 20);
        DrawText(effectDesc[i].c_str(), box.x + (box.width - effectDescWidth)/2, box.y + 415 + i * 23, 20, BLACK);
    }

    string costText = "Cost: " + to_string(manager.getShopItem(itemIndex)->getCost());
    int costTextWidth = MeasureText(costText.c_str(), 20);
    DrawText(costText.c_str(), box.x + (box.width - costTextWidth)/2, box.y + 480, 20, BLACK);

    string consumableText;
    if (manager.getShopItem(itemIndex)->isConsumableTrue()) {
        consumableText = "CONSUMABLE: Lasts ";
        if (manager.getShopItem(itemIndex)->getTurnsLast() == 0)
            consumableText += to_string(manager.getShopItem(itemIndex)->getTurnsLast()+1) + " Turn";
        else consumableText += to_string(manager.getShopItem(itemIndex)->getTurnsLast()+1) + " Turns";
    }
    else consumableText = "NON-CONSUMABLE";
    int consumableTextWidth = MeasureText(consumableText.c_str(), 18);
    DrawText(consumableText.c_str(), box.x + (box.width - consumableTextWidth)/2, box.y + 630, 18, BLACK);
}

void BuyItemPopup::showItem(unsigned index) {
    itemIndex = index;
    icon.setTexture(manager.getShopItem(itemIndex)->getIcon().c_str());
    needToUpdateDesc = true;
    visible = true;
}
