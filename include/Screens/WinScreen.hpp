#ifndef WINSCREEN_HPP
#define WINSCREEN_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class WinScreen : public IScreen {
    public:
        WinScreen(ScreenManager& manager);
        ~WinScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        
        
    private:
        ScreenManager& manager;
        Texture2D background;
        Button exitGameButton;
        Button toTitleScreenButton;
        
};

#endif