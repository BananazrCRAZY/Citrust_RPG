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

    string name;
    if (equipped) name = player->getBattleItem(itemIndex)->getName();
    else name = player->getInventoryItem(itemIndex)->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 30, 30, BLACK);

    if (needToUpdateDesc) {
        string message;
        if (equipped) message = player->getBattleItem(itemIndex)->getDescription();
        else message = player->getInventoryItem(itemIndex)->getDescription();
        reshapeMsg(message, itemDesc, itemLines, 20);
    }
    for (unsigned i = 0; i < itemLines; i++) {
        int textWidthDesc = MeasureText(itemDesc[i].c_str(), 20);
        DrawText(itemDesc[i].c_str(), box.x + (box.width - textWidthDesc)/2, box.y + 340 + i * 23, 20, BLACK);
    }

    if (needToUpdateDesc) {
    string effectDescMsg;
        if (equipped) effectDescMsg = player->getBattleItem(itemIndex)->getStatus()->getName()
            + ": " + player->getBattleItem(itemIndex)->getStatus()->getDescription();
        else effectDescMsg = player->getInventoryItem(itemIndex)->getStatus()->getName()
            + ": " + player->getInventoryItem(itemIndex)->getStatus()->getDescription();
        reshapeMsg(effectDescMsg, effectDesc, effectLines, 20);
        needToUpdateDesc = false;
    }
    for (unsigned i = 0; i < effectLines; i++) {
        int effectDescWidth = MeasureText(effectDesc[i].c_str(), 20);
        DrawText(effectDesc[i].c_str(), box.x + (box.width - effectDescWidth)/2, box.y + 415 + i * 23, 20, BLACK);
    }

    string consumableText = "NON-CONSUMABLE";
    if (equipped) {
        if (player->getBattleItem(itemIndex)->isConsumableTrue()) {
            consumableText = "CONSUMABLE: Lasts ";
            if (player->getBattleItem(itemIndex)->getTurnsLast() == 0)
                consumableText += to_string(player->getBattleItem(itemIndex)->getTurnsLast()+1) + " Turn";
            else consumableText += to_string(player->getBattleItem(itemIndex)->getTurnsLast()+1) + " Turns";
        }
    } else if (player->getInventoryItem(itemIndex)->isConsumableTrue()) {
        if (player->getInventoryItem(itemIndex)->isConsumableTrue()) {
            consumableText = "CONSUMABLE: Lasts ";
            if (player->getInventoryItem(itemIndex)->getTurnsLast() == 0)
                consumableText += to_string(player->getInventoryItem(itemIndex)->getTurnsLast()+1) + " Turn";
            else consumableText += to_string(player->getInventoryItem(itemIndex)->getTurnsLast()+1) + " Turns";
        }
    }
    int consumableTextWidth = MeasureText(consumableText.c_str(), 18);
    DrawText(consumableText.c_str(), box.x + (box.width - consumableTextWidth)/2, box.y + 630, 18, BLACK);
}

void EquipPopup::showItem(unsigned index) {
    itemIndex = index;
    if (equipped) {
        icon.setTexture(player->getBattleItem(itemIndex)->getIcon().c_str());
        secondButton.SetTexture("Graphics/Buttons/unequipButton.png", .84);  // equipped item, can be unequipped
    } else {
        icon.setTexture(player->getInventoryItem(itemIndex)->getIcon().c_str());
        if (player->getNumberBattleItems() >= 6) secondButton.SetTexture("Graphics/Buttons/equipButtonGray.png", .82);  // if non equipped item cant be equipped
        else secondButton.SetTexture("Graphics/Buttons/equipButton.png", .82);  // if non equipped item can be equipped
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
