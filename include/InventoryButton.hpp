#pragma once
#include <raylib.h>
#include "SolidButton.hpp"

class InventoryButton : public SolidButton {
    Color buttonBack;

    public:
        InventoryButton(const char *imagePath, Vector2 buttonPosition, float buttonWidth, float buttonHeight, Color backing)
            : SolidButton(imagePath, buttonPosition, buttonWidth, buttonHeight)
            , buttonBack(backing)
        {}

        void Draw() {
            DrawRectangleRec(buttonArea, buttonBack);
            DrawRectangleLinesEx(buttonArea, 2, BLACK);
            SolidButton::Draw();
        }

        void setBackingColor(Color backing) { buttonBack = backing; }
};