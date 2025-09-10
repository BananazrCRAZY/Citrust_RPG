#pragma once
#include "include/Buttons/button.hpp"
#include "ItemPopup.hpp"
#include "include/Objects/Player.h"

class EquipPopup : public ItemPopup {
    Player* player;
    bool equipped;

    public:
        EquipPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            unsigned index, ScreenManager& m, Player* p);
        void Update(const Vector2& mousePos, bool mouseClicked);
        void Draw();
        void showItem(unsigned);
        void setEquipped(bool);
        bool isEquipped() const;
};