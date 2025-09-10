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

    string name = player->getBattleItem(itemIndex)->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 30, 30, BLACK);

    if (needToUpdateDesc) {
        string message = player->getBattleItem(itemIndex)->getDescription();
        reshapeMsg(message, itemDesc, itemLines, 20);
        needToUpdateDesc = false;
    }
    for (unsigned i = 0; i < itemLines; i++) {
        int textWidthDesc = MeasureText(itemDesc[i].c_str(), 20);
        DrawText(itemDesc[i].c_str(), box.x + (box.width - textWidthDesc)/2, box.y + 365 + i * 23, 20, BLACK);
    }

    // cooldown count
    if (player->getBattleItem(itemIndex)->isConsumableTrue()) {
        string cooldownText;
        if (usable) cooldownText = "COOLDOWN AFTER USE: " + to_string(player->getBattleItem(itemIndex)->getCooldownDefault()) + " TURNS";
        else if (player->getBattleItem(itemIndex)->getCooldown() == 1) cooldownText = "COOLDOWN: 1 TURN LEFT";
        else cooldownText = "COOLDOWN: " + to_string(player->getBattleItem(itemIndex)->getCooldown()) + " TURNS LEFT";
        int cooldownTextWidth = MeasureText(cooldownText.c_str(), 20);
        DrawText(cooldownText.c_str(), box.x + (box.width - cooldownTextWidth)/2, box.y + 435, 20, BLACK);
    }

    string consumableText;
    if (player->getBattleItem(itemIndex)->isConsumableTrue()) {
        consumableText = "CONSUMABLE: Lasts ";
        if (player->getBattleItem(itemIndex)->getTurnsLast() == 0)
            consumableText += to_string(player->getBattleItem(itemIndex)->getTurnsLast()+1) + " Turn";
        else consumableText += to_string(player->getBattleItem(itemIndex)->getTurnsLast()+1) + " Turns";
    }
    else consumableText = "NON-CONSUMABLE";
    int consumableTextWidth = MeasureText(consumableText.c_str(), 20);
    DrawText(consumableText.c_str(), box.x + (box.width - consumableTextWidth)/2, box.y + 630, 20, BLACK);
}

void InventoryPopup::showItem(unsigned index) {
    itemIndex = index;
    icon.setTexture(player->getBattleItem(itemIndex)->getIcon().c_str());
    setUsable();
    needToUpdateDesc = true;
    visible = true;
}

void InventoryPopup::setUsable() {
    if (player->getBattleItem(itemIndex)->getCooldown() > 0 || !player->getBattleItem(itemIndex)->isConsumableTrue()) usable = false;
    else usable = true;
    if (usable) secondButton.SetTexture("Graphics/Buttons/useButton.png", .82);
    else secondButton.SetTexture("Graphics/Buttons/useButtonGray.png", .83);
}