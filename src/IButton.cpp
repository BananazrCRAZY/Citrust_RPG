#include "include/Buttons/IButton.hpp"

// Button Constructor
IButton::IButton (Vector2 buttonPosition) : position(buttonPosition) 
{
    size = {0, 0};
}

// Checks whether button is pressed by mouse
bool IButton::isPressed(Vector2 mousePos, bool mousePressed) {

    Rectangle buttonArea = {position.x, position.y, size.x, size.y};
    
    // if mouse is hovering over button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea) && mousePressed){
        return true;
    }

    return false;
}

float IButton::getXPos() const { return position.x; }
float IButton::getYPos() const { return position.y; }
float IButton::getXSize() const { return size.x; }
float IButton::getYSize() const { return size.y; }

void IButton::setXPos(float x) { position.x = x; }
void IButton::setYPos(float y) { position.y = y; }