#include "include/TextButton.hpp"

TextButton::TextButton (Vector2 buttonPos, Vector2 buttonSize, string initialText, Color color) :
    textButtonPosition(buttonPos)
    , textButtonSize(buttonSize)
    , text(initialText)
    , backing(color)
{
    textButtonArea = {textButtonPosition.x, textButtonPosition.y, static_cast<float>(buttonSize.x), static_cast<float>(buttonSize.y)};
}

void TextButton::Draw() {
    DrawRectangleRec(textButtonArea, backing);

    int textWidth = MeasureText(text.c_str(), 15);
    DrawText(text.c_str(), textButtonArea.x + (textButtonArea.width/2) - (textWidth/2), textButtonArea.y + (textButtonArea.height/2) - 7.5, 15, BLACK);
    DrawRectangleLinesEx(textButtonArea, 3, DARKGRAY);
}

bool TextButton::isPressed(Vector2 mousePos, bool mousePressed) {
    // if mouse is hovering over Button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, textButtonArea)) {
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

float TextButton::getXPos() const { return textButtonPosition.x; }
float TextButton::getYPos() const { return textButtonPosition.y; }
float TextButton::getXSize() const { return textButtonSize.x; }
float TextButton::getYSize() const { return textButtonSize.y; }