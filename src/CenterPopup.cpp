#include "include/Popups/CenterPopup.hpp"
#include "include/Global.hpp"
#include <iostream>
#include <raylib.h>

CenterPopup::CenterPopup(float duration)
    : duration(duration), 
    timer(0.0f),
    visible(false),
    message(""),
    numberOfLines(0),
    fontSize(30),
    fontColor(BLACK),
    backing(LIGHTGRAY),
    maxWidth(WINDOW_X - 600)
{
    displayMsg[0] = "";
    displayMsg[1] = "";
    displayMsg[2] = "";
}

void CenterPopup::show(const string& msg, int size, Color fontCol, Color backCol) {
    message = msg;
    fontSize = size;
    reshapeMsg();
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

    float boxWidth = 0;
    for (int i = 0; i < numberOfLines; i++) {
        int textWidth = MeasureText(displayMsg[i].c_str(), fontSize);
        if (textWidth > boxWidth) boxWidth = textWidth;
    }
    boxWidth += 40;

    float xPos = (WINDOW_X - boxWidth) / 2;
    float boxHeight = numberOfLines * fontSize + 60;
    float yPos = (WINDOW_Y - boxHeight) / 2;
    Rectangle box = { xPos, yPos, boxWidth, boxHeight};
    DrawRectangleRec(box, backing);
    DrawRectangleLinesEx(box, 3, BLACK);

    for (int i = 0; i < numberOfLines; i++) DrawText(displayMsg[i].c_str(), box.x + 20, box.y + 30 + i * fontSize, fontSize, fontColor);
}

bool CenterPopup::isVisible() { return visible; }

void CenterPopup::setDuration(float time) { duration = time; }

void CenterPopup::reshapeMsg() {
    displayMsg[0] = "";
    displayMsg[1] = "";
    displayMsg[2] = "";
    numberOfLines = 0;

    int msgWidth = MeasureText(message.c_str(), fontSize);
    if (msgWidth >= maxWidth) {
        int widthOfChar = msgWidth / message.size();
        int charCount = 0;
        for (int i = 0; i < message.length(); i++) {
            if ((charCount * widthOfChar) > (maxWidth - 50)) {
                if (message[i] == ' ') {
                    numberOfLines++;
                    charCount = 0;
                }
            } else {
                displayMsg[numberOfLines] += message[i];
            }
            charCount++;
        }
    } else displayMsg[0] = message;

    numberOfLines++;

    if (numberOfLines > 3) {
        std::cerr << "Error: CenterPopup, reshapeMsg(), numberOfLines > 3";
        exit(1);
    }
}