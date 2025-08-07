#include "include/SolidButton.hpp"

// Button Constructor
SolidButton::SolidButton (const char *imagePath, Vector2 buttonPosition, float buttonWidth, float buttonHeight) :
    position(buttonPosition),
    buttonWidth(buttonWidth),
    buttonHeight(buttonHeight)
    {

    // Uses Image class first as it is resizeable to scale; Texture class is not
    Image image = LoadImage(imagePath);

    int imageWidth = static_cast<int>(image.width * .3);
    int imageHeight = static_cast<int>(image.height * .3);
    while (imageHeight >= buttonHeight || imageWidth >= buttonWidth) {
        imageHeight *= .85;
        imageWidth *= .85;
    }

    ImageResize(&image, imageWidth, imageHeight);

    // Converts image into texture
    texture = LoadTextureFromImage(image);

    // Deletes image from heap as it is no longer needed
    UnloadImage(image);

    // math to figure out where to center image
    float imageX = buttonWidth / 2;
    float x = imageWidth / 2;
    imageX -= x;
    imagePosition.x = imageX + position.x;

    float imageY = buttonHeight / 2;
    float y = imageHeight / 2;
    imageY -= y;
    imagePosition.y = imageY + position.y;
}

// Destructor
SolidButton::~SolidButton() {
    UnloadTexture(texture);
}

// Creates button onto window
void SolidButton::Draw() {
    DrawTextureV(texture, imagePosition, WHITE);
}

// Checks whether button is pressed by mouse
bool SolidButton::isPressed(Vector2 mousePos, bool mousePressed) {

    Rectangle buttonArea = {position.x, position.y, buttonWidth, buttonHeight};
    
    // if mouse is hovering over button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea) && mousePressed){
        return true;
    }

    return false;
}
