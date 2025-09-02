#pragma once
#include <string>
#include <raylib.h>

using std::string;

class TextButton {
    public:
        TextButton(Vector2 buttonPos, Vector2 buttonSize, string initialText, Color color, int fSize);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

        void setColor(Color color);
        void setText(string text);
        float getXPos() const;
        float getYPos() const;
        float getXSize() const;
        float getYSize() const;
        void setButtonXPos(float);
        void setButtonYPos(float);
    private:
        Vector2 textButtonPosition;
        Vector2 textButtonSize;
        string text;
        Rectangle textButtonArea;
        Color backing;
        int fontSize;
};