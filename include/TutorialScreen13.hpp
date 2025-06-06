#ifndef TUTORIALSCREEN13_HPP
#define TUTORIALSCREEN13_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen13 : public IScreen {
    public:
        TutorialScreen13(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen13() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 