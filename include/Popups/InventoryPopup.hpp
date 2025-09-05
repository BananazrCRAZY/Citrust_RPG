#pragma once
#include "include/Buttons/button.hpp"
#include "IndefinitePopup.hpp"
#include "include/Objects/Player.h"
#include "include/Screens/ScreenManager.hpp"
#include "include/Buttons/SolidButton.hpp"
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
