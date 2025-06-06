#ifndef SHOPSCREEN_HPP
#define SHOPSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
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
        Button item1;
        Button item2;
        Button item3;
        Button item4;
        Button item5;
        Button item6;
        Button backButton;
        Texture2D background;
};

#endif 