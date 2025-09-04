#pragma once
#include <raylib.h>

class IButton {
    public:
        IButton(Vector2 buttonPosition);
        virtual void Draw() = 0;
        bool isPressed(Vector2 mousePos, bool mousePressed);

        float getXPos() const;
        float getYPos() const;
        float getXSize() const;
        float getYSize() const;
        void setXPos(float x);
        void setYPos(float y);
    protected:
        Vector2 position;
        Vector2 size;
};