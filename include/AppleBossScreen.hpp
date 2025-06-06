#ifndef APPLEBOSSSCREEN_HPP
#define APPLEBOSSSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "Popup.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class AppleBossScreen : public IScreen {
    public:
        AppleBossScreen(ScreenManager& manager, bool& exitFlag);
        ~AppleBossScreen() override;
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
        Button playerHPButton;
        Button bossHPButton;
        Button spCounterButton;
        Button skillButton;
        Button attackButton;
        Button inventoryButton;
};

#endif 