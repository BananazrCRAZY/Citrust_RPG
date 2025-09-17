#include "include/Buttons/button.hpp"

// Button Constructor
Button::Button (const char *imagePath, Vector2 imagePosition, float scale) : IButton::IButton(imagePosition) {
    SetTexture(imagePath, scale);
}

// Destructor
Button::~Button() {
    if (texture.id != 0) UnloadTexture(texture);
}

// Creates button onto window
void Button::Draw() {
    DrawTextureV(texture, position, WHITE);
}

void Button::SetTexture(const char* imagePath, float scale) {
    // without if causes button textures to be messed up
    if (texture.id != 0) UnloadTexture(texture);

    Image image = LoadImage(imagePath);

    // scaling & resizing
    float newWidth = static_cast<int>(image.width * scale);
    float newHeight = static_cast<int>(image.height * scale);
    size = {newWidth, newHeight};
    ImageResize(&image, newWidth, newHeight);
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}