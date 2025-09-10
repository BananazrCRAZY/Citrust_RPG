#pragma once
#include "include/Buttons/button.hpp"
#include "ItemPopup.hpp"
#include <string>
#include <raylib.h>

using std::string;

class BuyItemPopup : public ItemPopup {
    public:
        BuyItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            unsigned index, ScreenManager& sm);
        void Update(const Vector2& mousePos, bool mouseClicked);
        void Draw();
        void showItem(unsigned);
};
