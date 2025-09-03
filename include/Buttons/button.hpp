#pragma once
#include <raylib.h>

class Button {
    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

        float getXPos() const;
        float getYPos() const;
        float getXSize() const;
        float getYSize() const;
        void SetTexture(const char* imagePath, float scale);        // for less button creations
    private:
        Texture2D texture;
        Vector2 position;           // Vector2 data type representing vector w/ x & y components
        Vector2 size;
};