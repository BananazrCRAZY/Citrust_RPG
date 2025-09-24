#pragma once
#include <string>
#include <raylib.h>
#include "IButton.hpp"

using std::string;

class TextButton : public IButton{
    public:
        TextButton(Vector2 buttonPos, Vector2 buttonSize, string initialText, Color color, int fSize);
        void Draw();
        bool isPressed(Vector2 mousePos, bool mousePressed);

        void setColor(Color color);
        void setText(string text);
    private:
        string text;
        Color backing;
        int fontSize;
};