#ifndef LOSESCREEN_HPP
#define LOSESCREEN_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class LoseScreen : public IScreen {
    public:
        LoseScreen(ScreenManager& manager);
        ~LoseScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        
        
    private:
        ScreenManager& manager;
        Texture2D background;
        Button exitGameButton;
        Button tryAgainButton;
        Button toTitleScreenButton;
        
};

#endif