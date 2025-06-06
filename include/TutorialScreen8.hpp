#ifndef TUTORIALSCREEN8_HPP
#define TUTORIALSCREEN8_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen8 : public IScreen {
    public:
        TutorialScreen8(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen8() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 