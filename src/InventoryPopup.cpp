#include "include/Popups/InventoryPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

InventoryPopup::InventoryPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& mgr, Player* p) : 
    ItemPopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath, index, mgr, "Graphics/Buttons/useButtonGray.png"),
    player(p)
{}

void InventoryPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    IndefinitePopup::Update(mousePos, mouseClicked);

    if (usable) {
        if (secondButton.isPressed(mousePos, mouseClicked)) {
            visible = false;
            manager.setInput(itemIndex+2);
        }
    }
}

void InventoryPopup::Draw() {
    if (!visible) return;
    ItemPopup::Draw();

    // cooldown count
    if (item->isConsumableTrue()) {
        string cooldownText;
        if (usable) {
            if (player->getBattleItem(itemIndex)->getCooldownDefault() == 1) cooldownText = "Cooldown After Use: 1 Turn";
            else cooldownText = "Cooldown After Use: " + to_string(player->getBattleItem(itemIndex)->getCooldownDefault()) + " Turns";
        } else if (player->getBattleItem(itemIndex)->getCooldown() == 1) cooldownText = "Cooldown: 1 Turn Left";
        else cooldownText = "Cooldown: " + to_string(player->getBattleItem(itemIndex)->getCooldown()) + " Turns Left";
        int cooldownTextWidth = MeasureText(cooldownText.c_str(), 20);
        DrawText(cooldownText.c_str(), box.x + (box.width - cooldownTextWidth)/2, box.y + 610, 20, BLACK);
    }
}

void InventoryPopup::showItem(unsigned index) {
    itemIndex = index;
    item = player->getBattleItem(index);
    icon.setTexture(item->getIcon().c_str());
    setUsable();
    needToUpdateDesc = true;
    visible = true;
}

void InventoryPopup::setUsable() {
    if (item->getCooldown() > 0 || !item->isConsumableTrue()) usable = false;
    else usable = true;
    if (usable) secondButton.SetTexture("Graphics/Buttons/useButton.png", .82);
    else secondButton.SetTexture("Graphics/Buttons/useButtonGray.png", .83);
}