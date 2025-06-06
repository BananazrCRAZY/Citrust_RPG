#ifndef INTERLUDESCREEN_HPP
#define INTERLUDESCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class InterludeScreen : public IScreen {
    public:
        InterludeScreen(ScreenManager& manager, bool& exitFlag);
        ~InterludeScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Button shopButton;
        Button inventoryButton;
        Button bossButton;
        Button quitButton;
        Texture2D background;
};

#endif 