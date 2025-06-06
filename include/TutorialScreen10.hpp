#ifndef TUTORIALSCREEN10_HPP
#define TUTORIALSCREEN10_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen10 : public IScreen {
    public:
        TutorialScreen10(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen10() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 