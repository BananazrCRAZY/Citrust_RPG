#include "include/button.hpp"

// Button Constructor
Button::Button(const char *imagePath, Vector2 imagePosition, float scale) {

    // Uses Image class first as it is resizeable to scale; Texture class is not
    Image image = LoadImage(imagePath);

    int newWidth = static_cast<int>(image.width * scale);
    int newHeight = static_cast<int>(image.height * scale);

    ImageResize(&image, newWidth, newHeight);

    // Converts image into texture
    texture = LoadTextureFromImage(image);

    // Deletes image from heap as it is no longer needed
    UnloadImage(image);

    position = imagePosition;
}

// Destructor
Button::~Button() {
    UnloadTexture(texture);
}

// Creates button onto window
void Button::Draw() {
    DrawTextureV(texture, position, WHITE);
}

// Checks whether button is pressed by mouse
bool Button::isPressed(Vector2 mousePos, bool mousePressed) {

    Rectangle buttonArea = {position.x, position.y, static_cast<float>(texture.width), static_cast<float>(texture.height)};
    
    // if mouse is hovering over button area (rectangular shape) and is pressed
    if (CheckCollisionPointRec(mousePos, buttonArea) && mousePressed){
        return true;
    }

    return false;
}
