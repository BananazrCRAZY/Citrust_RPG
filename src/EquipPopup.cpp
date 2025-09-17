#include "include/Popups/EquipPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

EquipPopup::EquipPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& m, Player* p) : 
    ItemPopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath, index, m, "Graphics/blank.png"),
    player(p),
    equipped(false)
{}

void EquipPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    IndefinitePopup::Update(mousePos, mouseClicked);

    if (!equipped) {
        if (player->getNumberBattleItems() >= 6) return;
        if (secondButton.isPressed(mousePos, mouseClicked)) {
            visible = false;
            manager.setInput(14+itemIndex);
            return;
        }
    } else if (secondButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        manager.setInput(8+itemIndex);
        return;
    }
}

void EquipPopup::Draw() {
    if (!visible) return;
    ItemPopup::Draw();

    if (item->isConsumableTrue()) {
        string cooldownText;
        if (item->getCooldownDefault() == 1) cooldownText = "Cooldown After Use: 1 Turn";
        else cooldownText = "Cooldown After Use: " + to_string(item->getCooldownDefault()) + " Turns";
        int cooldownTextWidth = MeasureText(cooldownText.c_str(), 20);
        DrawText(cooldownText.c_str(), box.x + (box.width - cooldownTextWidth)/2, box.y + 610, 20, BLACK);
    }
}

void EquipPopup::showItem(unsigned index) {
    itemIndex = index;
    if (equipped) {
        icon.setTexture(player->getBattleItem(index)->getIcon().c_str());
        secondButton.SetTexture("Graphics/Buttons/unequipButton.png", .84);  // equipped item, can be unequipped
        item = player->getBattleItem(index);
    } else {
        icon.setTexture(player->getInventoryItem(index)->getIcon().c_str());
        if (player->getNumberBattleItems() >= 6) secondButton.SetTexture("Graphics/Buttons/equipButtonGray.png", .82);  // if non equipped item cant be equipped
        else secondButton.SetTexture("Graphics/Buttons/equipButton.png", .82);  // if non equipped item can be equipped
        item = player->getInventoryItem(index);
    }
    needToUpdateDesc = true;
    visible = true;
}

void EquipPopup::setEquipped(bool set) {
    equipped = set;
}

bool EquipPopup::isEquipped() const {
    return equipped;
}
