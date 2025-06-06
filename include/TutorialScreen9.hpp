#ifndef TUTORIALSCREEN9_HPP
#define TUTORIALSCREEN9_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen9 : public IScreen {
    public:
        TutorialScreen9(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen9() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 