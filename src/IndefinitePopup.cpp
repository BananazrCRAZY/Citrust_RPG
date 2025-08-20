#include "include/IndefinitePopup.hpp"
#include <raylib.h>

#include <iostream>

IndefinitePopup::IndefinitePopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath) :
    position(popupPosition),
    size(popupSize),
    visible(false),
    cancelButton(imagePath, buttonPosition, buttonScale),
    box({position.x, position.y, size.x, size.y})
{}

void IndefinitePopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    if (cancelButton.isPressed(mousePos, mouseClicked)) visible = false;
}

void IndefinitePopup::Draw() {
    if (!visible) return;
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 3, DARKGRAY);
    cancelButton.Draw();
}
