#include "include/Buttons/SolidButton.hpp"

// Button Constructor
SolidButton::SolidButton (const char *imagePath, Vector2 buttonPosition, float buttonWidth, float buttonHeight) :
    position(buttonPosition),
    buttonWidth(buttonWidth),
    buttonHeight(buttonHeight),
    imagePathHolder(imagePath)
{
    setTexture(imagePath);
}

// Destructor
SolidButton::~SolidButton() {
    if (texture.id != 0) UnloadTexture(texture);
}

// Creates button onto window
void SolidButton::Draw() {
    DrawTextureV(texture, imagePosition, WHITE);
}

// Checks whether button is pressed by mouse
bool SolidButton::isPressed(Vector2 mousePos, bool mousePressed) {
    if (!active) return false;
    
    // if mouse is hovering over button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea) && mousePressed){
        return true;
    }

    return false;
}

void SolidButton::updateImagePosition(float imageWidth, float imageHeight) {
    buttonArea = {position.x, position.y, buttonWidth, buttonHeight};
    float imageX = (buttonWidth / 2) - (imageWidth / 2);
    float imageY = (buttonHeight / 2) - (imageHeight / 2);
    imagePosition = { imageX + position.x, imageY + position.y };
}

void SolidButton::setTexture(const char* imagePath) {
    // without if causes button textures to be messed up
    if (texture.id != 0) UnloadTexture(texture);

    // Uses Image class first as it is resizeable to scale; Texture class is not
    Image image = LoadImage(imagePath);

    int imageWidth = image.width;
    int imageHeight = image.height;
    while (imageHeight >= buttonHeight || imageWidth >= buttonWidth) {
        imageHeight *= .85;
        imageWidth *= .85;
    }

    ImageResize(&image, imageWidth, imageHeight);
    // Converts image into texture
    texture = LoadTextureFromImage(image);

    // Deletes image from heap as it is no longer needed
    UnloadImage(image);

    // recalc placement based on button position
    updateImagePosition(imageWidth, imageHeight);
}

void SolidButton::disableButton() { active = false; }
void SolidButton::enablebutton() { active = true; }
float SolidButton::getButtonXPos() const { return position.x; }
float SolidButton::getButtonYPos() const { return position.y; }

void SolidButton::setButtonXPos(float x) {
    position.x = x;
    updateImagePosition(texture.width, texture.height);
}

void SolidButton::setButtonYPos(float y) {
    position.y = y;
    updateImagePosition(texture.width, texture.height);
}
