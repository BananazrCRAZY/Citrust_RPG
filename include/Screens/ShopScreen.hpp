#ifndef SHOPSCREEN_HPP
#define SHOPSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include "include/Buttons/SolidButton.hpp"
#include "include/Objects/Shop.h"
#include "include/Popups/BuyItemPopup.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class ShopScreen : public IScreen {
    public:
        ShopScreen(ScreenManager& manager, bool& exitFlag);
        ~ShopScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        SolidButton* items[6];
        Button backButton;
        Button refreshButton;
        Texture2D background;
        BuyItemPopup menu;
        Shop* shop;

        void resetItems();
};

#endif 