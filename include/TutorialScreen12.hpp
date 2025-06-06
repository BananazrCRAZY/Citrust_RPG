#ifndef TUTORIALSCREEN12_HPP
#define TUTORIALSCREEN12_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen12 : public IScreen {
    public:
        TutorialScreen12(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen12() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 