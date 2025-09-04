#include "include/Buttons/button.hpp"

// Button Constructor
Button::Button (const char *imagePath, Vector2 imagePosition, float scale) : IButton::IButton(imagePosition) {

    // Uses Image class first as it is resizeable to scale; Texture class is not
    Image image = LoadImage(imagePath);

    float newWidth = static_cast<int>(image.width * scale);
    float newHeight = static_cast<int>(image.height * scale);
    size = {newWidth, newHeight};

    ImageResize(&image, newWidth, newHeight);

    // Converts image into texture
    texture = LoadTextureFromImage(image);

    // Deletes image from heap as it is no longer needed
    UnloadImage(image);
}

// Destructor
Button::~Button() {
    UnloadTexture(texture);
}

// Creates button onto window
void Button::Draw() {
    DrawTextureV(texture, position, WHITE);
}

void Button::SetTexture(const char* imagePath, float scale) {
    UnloadTexture(texture);  // unloads old texture first

    Image image = LoadImage(imagePath);

    // scaling & resizing
    int newWidth = static_cast<int>(image.width * scale);
    int newHeight = static_cast<int>(image.height * scale);
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}