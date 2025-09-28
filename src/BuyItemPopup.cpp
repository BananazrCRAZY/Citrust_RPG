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

    string costText = "Cost: " + to_string(item->getCost());
    int costTextWidth = MeasureText(costText.c_str(), 20);
    DrawText(costText.c_str(), box.x + (box.width - costTextWidth)/2, box.y + 500, 20, BLACK);

    if (item->isConsumableTrue()) {
        string cooldownText;
        if (item->getCooldownDefault() == 1) cooldownText = "Cooldown After Use: 1 Turn";
        else cooldownText = "Cooldown After Use: " + to_string(item->getCooldownDefault()) + " Turns";
        int cooldownTextWidth = MeasureText(cooldownText.c_str(), 20);
        DrawText(cooldownText.c_str(), box.x + (box.width - cooldownTextWidth)/2, box.y + 610, 20, BLACK);
    }
}

void BuyItemPopup::showItem(unsigned index) {
    itemIndex = index;
    item = manager.getShopItem(index);
    icon.setTexture(item->getIcon().c_str());
    needToUpdateDesc = true;
    visible = true;
}
