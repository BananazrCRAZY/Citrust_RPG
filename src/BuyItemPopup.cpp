#include "include/Popups/BuyItemPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

BuyItemPopup::BuyItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& sm) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    itemIndex(index),
    manager(sm),
    buyButton("Graphics/Buttons/buyButton.png", {900, 600}, .81),
    icon("", {700, 200}, 200, 200)
{}

void BuyItemPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    IndefinitePopup::Update(mousePos, mouseClicked);

    if (buyButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        manager.setInput(itemIndex+1);
    }
}

void BuyItemPopup::Draw() {
    if (!visible) return;
    IndefinitePopup::Draw();
    buyButton.Draw();
    icon.Draw();

    string name = manager.getShopItem(itemIndex)->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 30, 30, BLACK);

    string message = manager.getShopItem(itemIndex)->getDescription();
    int textWidthDesc = MeasureText(message.c_str(), 20);
    if (textWidthDesc >= 700) {
        int charCount = 0;
        for (int i = 0; i < message.length(); i++) {
            if (charCount > 65) {
                if (message[i] == ' ') {
                    message[i] = '\n';
                    charCount = 0;
                }
            }
            charCount++;
        }
        textWidthDesc = MeasureText(message.c_str(), 20);
    }
    DrawText(message.c_str(), box.x + (box.width - textWidthDesc)/2, box.y + 365, 20, BLACK);

    string costText = "Cost: " + to_string(manager.getShopItem(itemIndex)->getCost());
    int costTextWidth = MeasureText(costText.c_str(), 20);
    DrawText(costText.c_str(), box.x + (box.width - costTextWidth)/2, box.y + 435, 20, BLACK);

    string consumableText;
    if (manager.getShopItem(itemIndex)->isConsumableTrue()) consumableText = "CONSUMABLE";
    else consumableText = "NON-CONSUMABLE";
    int consumableTextWidth = MeasureText(consumableText.c_str(), 18);
    DrawText(consumableText.c_str(), box.x + (box.width - consumableTextWidth)/2, box.y + 630, 18, BLACK);
}

void BuyItemPopup::showItem(unsigned index) {
    itemIndex = index;
    icon.setTexture(manager.getShopItem(itemIndex)->getIcon().c_str());
    visible = true;
}
