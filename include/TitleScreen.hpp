#ifndef TITLESCREEN_HPP
#define TITLESCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TitleScreen : public IScreen {
    public:
        TitleScreen(ScreenManager& manager, bool& exitFlag);
        ~TitleScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Button startButton;
        Button loadButton;
        Button quitButton;
        Texture2D background;
};

#endif 