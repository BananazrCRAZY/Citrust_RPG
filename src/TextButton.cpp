#include "include/Buttons/TextButton.hpp"

TextButton::TextButton (Vector2 buttonPos, Vector2 buttonSize, string initialText, Color color, int fSize) :
    IButton(buttonPos, buttonSize)
    , text(initialText)
    , backing(color)
    , fontSize(fSize)
{}

void TextButton::Draw() {
    DrawRectangleRec(buttonArea, backing);

    int textWidth = MeasureText(text.c_str(), fontSize);
    DrawText(text.c_str(), buttonArea.x + (buttonArea.width/2) - (textWidth/2), buttonArea.y + (buttonArea.height/2) - 7.5, fontSize, BLACK);
    DrawRectangleLinesEx(buttonArea, 3, DARKGRAY);
}

bool TextButton::isPressed(Vector2 mousePos, bool mousePressed) {
    // if mouse is hovering over Button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea)) {
        if (mousePressed) return true;
    }

    return false;
}

void TextButton::setColor(Color color) {
    backing = color;
}

void TextButton::setText(string text) {
    text = text;
}
