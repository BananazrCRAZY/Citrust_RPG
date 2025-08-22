#include "include/EquipPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

EquipPopup::EquipPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& m, Player* p) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    itemIndex(index),
    manager(m), 
    player(p),
    equipButton("Graphics/Buttons/backButton.png", {900, 600}, .8),
    icon("", {700, 200}, 200, 200)
{}

void EquipPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    IndefinitePopup::Update(mousePos, mouseClicked);

    if (player->getNumberInventoryItems() >= 6) return;
    if (equipButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        manager.setInput(itemIndex+1);
    }
}

void EquipPopup::Draw() {
    if (!visible) return;
    IndefinitePopup::Draw();
    equipButton.Draw();
    icon.Draw();

    string name = player->getInventoryItem(itemIndex)->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 30, 30, BLACK);

    string message = player->getInventoryItem(itemIndex)->getDescription();
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

    string consumableText;
    if (player->getInventoryItem(itemIndex)->isConsumableTrue()) consumableText = "CONSUMABLE";
    else consumableText = "NON-CONSUMABLE";
    int consumableTextWidth = MeasureText(consumableText.c_str(), 18);
    DrawText(consumableText.c_str(), box.x + (box.width - consumableTextWidth)/2, box.y + 630, 18, BLACK);
}

void EquipPopup::showItem(unsigned index) {
    itemIndex = index;
    icon.setTexture(manager.getShopItem(itemIndex)->getIcon().c_str());
    if (player->getNumberInventoryItems() >= 6) equipButton.SetTexture("", .8);
    else equipButton.SetTexture("Graphics/Buttons/backButton.png", .8);
    visible = true;
}
