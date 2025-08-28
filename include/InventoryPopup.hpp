#pragma once
#include "include/button.hpp"
#include "include/IndefinitePopup.hpp"
#include "Player.h"
#include "ScreenManager.hpp"
#include "include/SolidButton.hpp"
#include <string>
#include <raylib.h>

using std::string;

class InventoryPopup : public IndefinitePopup {
    unsigned itemIndex;
    ScreenManager& manager;
    Player* player;
    Button useButton;
    SolidButton icon;
    bool usable;

    void setUsable();

    public:
        InventoryPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            unsigned index, ScreenManager& mgr, Player* p);
        void Update(const Vector2& mousePos, bool mouseClicked);
        void Draw();
        void showItem(unsigned);
};
