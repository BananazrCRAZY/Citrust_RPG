#ifndef TUTORIALSCREEN_HPP
#define TUTORIALSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen : public IScreen {
    public:
        TutorialScreen(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 