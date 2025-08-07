#include "include/IndefinitePopup.hpp"
#include <raylib.h>

IndefinitePopup::IndefinitePopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath) :
    position(popupPosition),
    size(popupSize),
    visible(false),
    cancelButton(imagePath, buttonPosition, buttonScale)
{}

void IndefinitePopup::Show(const std::string& msg) {
    message = msg;
    visible = true;
}

void IndefinitePopup::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!visible) return;
    if (cancelButton.isPressed(mousePos, mouseClicked)) visible = false;
}

void IndefinitePopup::Draw() {
    if (!visible) return;

    Rectangle box = { position.x, position.y, size.x, size.y };
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 3, DARKGRAY);
    cancelButton.Draw();

    // int textWidth = MeasureText(message.c_str(), 20);
    // DrawText(message.c_str(), box.x + (box.width - textWidth)/2, box.y + 30, 20, BLACK);
}
