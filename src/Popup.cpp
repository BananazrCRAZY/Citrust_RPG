#include "include/Popup.hpp"
#include <raylib.h>

Popup::Popup(float duration)
    : duration(duration), timer(0.0f), visible(false), message("") {}

void Popup::Show(const std::string& msg) {
    message = msg;
    timer = 0.0f;
    visible = true;
}

void Popup::Update() {
    if (!visible) return;

    timer += GetFrameTime();
    if (timer >= duration) {
        visible = false;
    }
}

void Popup::Draw() {
    if (!visible) return;

    Rectangle box = { 800, 600, 400, 80 };
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 3, DARKGRAY);

    int textWidth = MeasureText(message.c_str(), 20);
    DrawText(message.c_str(), box.x + (box.width - textWidth)/2, box.y + 30, 20, BLACK);
}

bool Popup::IsVisible() const {
    return visible;
}
