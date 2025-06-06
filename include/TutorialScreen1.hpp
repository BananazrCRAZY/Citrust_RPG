#ifndef TUTORIALSCREEN1_HPP
#define TUTORIALSCREEN1_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen1 : public IScreen {
    public:
        TutorialScreen1(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen1() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 