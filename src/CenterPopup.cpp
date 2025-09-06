#include "include/Popups/CenterPopup.hpp"
#include <raylib.h>

CenterPopup::CenterPopup(float duration)
    : duration(duration), 
    timer(0.0f),
    visible(false),
    message(""),
    fontSize(30),
    fontColor(BLACK),
    backing(LIGHTGRAY)
{}

void CenterPopup::show(const string& msg, int size, Color fontCol, Color backCol) {
    message = msg;
    fontSize = size;
    fontColor = fontCol;
    backing = backCol;
    visible = true;
}

void CenterPopup::Update() {
    if (!visible) return;

    timer += GetFrameTime();
    if (timer >= duration) {
        visible = false;
        timer = 0;
    }
}

void CenterPopup::Draw() {
    if (!visible) return;

    int textWidth = MeasureText(message.c_str(), fontSize);
    float boxWidth = 400;
    if (textWidth > boxWidth) boxWidth = textWidth + 40;

    float xPos = 800 - boxWidth / 2;
    float boxHeight = fontSize + 60;
    float yPos = 450 - boxHeight;
    Rectangle box = { xPos, yPos, boxWidth, boxHeight};
    DrawRectangleRec(box, backing);
    DrawRectangleLinesEx(box, 3, BLACK);

    DrawText(message.c_str(), box.x + (box.width - textWidth)/2, box.y + 30, fontSize, fontColor);
}

bool CenterPopup::isVisible() { return visible; }

void CenterPopup::setDuration(float time) { duration = time; }