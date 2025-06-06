#pragma once
#include <raylib.h>

class Button {
    public:
        Button(const char* imagePath, Vector2 imagePosition, float scale);
        ~Button();
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

        void SetTexture(const char* imagePath, float scale);        // for less button creations
    private:
        Texture2D texture;
        Vector2 position;           // Vector2 data type representing vector w/ x & y components

};