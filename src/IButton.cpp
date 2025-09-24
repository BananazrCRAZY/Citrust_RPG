#include "include/Buttons/IButton.hpp"

// Button Constructor
IButton::IButton (Vector2 buttonPosition, Vector2 buttonSize)
{
    buttonArea = {buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y};
}

// Checks whether button is pressed by mouse
bool IButton::isPressed(Vector2 mousePos, bool mousePressed) {    
    // if mouse is hovering over button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea) && mousePressed){
        return true;
    }

    return false;
}

float IButton::getXPos() const { return buttonArea.x; }
float IButton::getYPos() const { return buttonArea.y; }
float IButton::getXSize() const { return buttonArea.width; }
float IButton::getYSize() const { return buttonArea.height; }

void IButton::setXPos(float x) { buttonArea.x = x; }
void IButton::setYPos(float y) { buttonArea.y = y; }
void IButton::setWidth(float width) { buttonArea.width = width; }
void IButton::setHeight(float height) { buttonArea.height = height; }