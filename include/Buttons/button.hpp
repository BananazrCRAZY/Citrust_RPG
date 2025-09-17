#pragma once
#include "IButton.hpp"
#include <raylib.h>

class Button : public IButton {
    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        void Draw();

        void SetTexture(const char* imagePath, float scale);        // for less button creations
    private:
        Texture2D texture = {0};
};