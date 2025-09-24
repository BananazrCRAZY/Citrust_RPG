#pragma once
#include <raylib.h>

class IButton {
    public:
        IButton(Vector2 buttonPosition, Vector2 buttonSize);
        virtual void Draw() = 0;
        bool isPressed(Vector2 mousePos, bool mousePressed);

        float getXPos() const;
        float getYPos() const;
        float getXSize() const;
        float getYSize() const;
        void setXPos(float x);
        void setYPos(float y);
        void setWidth(float width);
        void setHeight(float height);
    protected:
        Rectangle buttonArea;
};