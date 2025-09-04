#include "include/Popups/Popup.hpp"
#include <raylib.h>

Popup::Popup(float duration)
    : duration(duration), timer(0.0f), visible(false), message(""), displayMessage(""), index(0) {}

void Popup::Show(const std::string& msg) {
    message = msg;
    getDisplayMessage();
    visible = true;
}

void Popup::Update() {
    if (!visible) return;

    timer += GetFrameTime();
    if (timer >= duration) {
        getDisplayMessage();
    }
}

void Popup::Draw() {
    if (!visible) return;

    int textWidth = MeasureText(displayMessage.c_str(), 20);
    float boxWidth = 400;
    if (textWidth > 400) boxWidth = textWidth + 40;

    Rectangle box = { 800, 600, boxWidth, 80 };
    DrawRectangleRec(box, LIGHTGRAY);
    DrawRectangleLinesEx(box, 3, DARKGRAY);

    DrawText(displayMessage.c_str(), box.x + (box.width - textWidth)/2, box.y + 30, 20, BLACK);
}

bool Popup::isVisible() { return visible; }

void Popup::getDisplayMessage() {
    displayMessage = "";
    if (message.length() > index) {
        for (index; index < message.length(); index++) {
            if (message[index] == '\n') {
                index++;
                break;
            }
            else displayMessage += message[index];
        }
    } else {
        visible = false;
        index = 0;
    }
    timer = 0.0f;
}