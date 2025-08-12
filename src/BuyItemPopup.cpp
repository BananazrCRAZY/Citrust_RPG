#include "include/BuyItemPopup.hpp"
#include <raylib.h>

BuyItemPopup::BuyItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& sm) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    itemIndex(index),
    manager(sm)
{}

void BuyItemPopup::Update(const Vector2& mousePos, bool mouseClicked) {
    IndefinitePopup::Update(mousePos, mouseClicked);

}

void BuyItemPopup::Draw() {
    IndefinitePopup::Draw();

}

void BuyItemPopup::showItem(unsigned index) {
    itemIndex = index;
    visible = true;
}

bool BuyItemPopup::isVisible() const {
    return visible;
}