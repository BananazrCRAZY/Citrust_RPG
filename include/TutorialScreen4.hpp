#ifndef TUTORIALSCREEN4_HPP
#define TUTORIALSCREEN4_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen4 : public IScreen {
    public:
        TutorialScreen4(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen4() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 