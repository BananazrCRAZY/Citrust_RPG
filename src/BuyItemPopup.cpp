#include "include/BuyItemPopup.hpp"
#include <raylib.h>

BuyItemPopup::BuyItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager sm) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    itemIndex(index),
    manager(sm)
{}

void Popup::Update() {
    if (!visible) return;

    timer += GetFrameTime();
    if (timer >= duration) {
        visible = false;
    }
}

void BuyItemPopup::Draw() {
    if (!visible) return;

    Rectangle box = { 800, 600, 400, 80 };
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 3, DARKGRAY);

    int textWidth = MeasureText(message.c_str(), 20);
    DrawText(message.c_str(), box.x + (box.width - textWidth)/2, box.y + 30, 20, BLACK);
}
