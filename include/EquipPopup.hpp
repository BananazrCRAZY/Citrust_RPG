#pragma once
#include "button.hpp"
#include "IndefinitePopup.hpp"
#include "Player.h"
#include "ScreenManager.hpp"
#include "SolidButton.hpp"

class EquipPopup : public IndefinitePopup {
    unsigned itemIndex;
    ScreenManager& manager;
    Button equipButton;
    SolidButton icon;
    Player* player;

    public:
        EquipPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            unsigned index, ScreenManager& m, Player* p);
        void Update(const Vector2& mousePos, bool mouseClicked);
        void Draw();
        void showItem(unsigned);
};