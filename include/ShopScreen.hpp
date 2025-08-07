#ifndef SHOPSCREEN_HPP
#define SHOPSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include "SolidButton.hpp"
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
        SolidButton item1;
        SolidButton item2;
        SolidButton item3;
        SolidButton item4;
        SolidButton item5;
        SolidButton item6;
        Button backButton;
        Texture2D background;
};

#endif 