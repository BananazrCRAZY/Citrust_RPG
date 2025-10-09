#pragma once
#include "include/Buttons/button.hpp"
#include "include/Screens/ScreenManager.hpp"
#include "IndefinitePopup.hpp"
#include <string>
#include <raylib.h>

using std::string;

class RefreshPopup : public IndefinitePopup {
    ScreenManager& mgr;
    Button refresh;
    bool hasEnough;
    int refreshCost = 50;

    public:
        RefreshPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath,
            ScreenManager& mgr);
        void Update(const Vector2& mousePos, bool mouseClicked);
        void Draw();
        void showPopup();
};
