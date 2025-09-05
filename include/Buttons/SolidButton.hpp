#pragma once
#include <raylib.h>

class SolidButton {
    public:
        SolidButton(const char*, Vector2, float, float);
        ~SolidButton();
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);
        void updateImagePosition(float imageWidth, float imageHeight);
        void setTexture(const char* imagePath);
        void disableButton();
        void enablebutton();
        float getButtonXPos() const;
        float getButtonYPos() const;
        void setButtonXPos(float);
        void setButtonYPos(float);
    protected:
        Texture2D texture;
        Vector2 position;           // Vector2 data type representing vector w/ x & y components
        float buttonWidth;
        float buttonHeight;
        Vector2 imagePosition;
        bool active = true;
        Rectangle buttonArea;
        const char * imagePathHolder;
};