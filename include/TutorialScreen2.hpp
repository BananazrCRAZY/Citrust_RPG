#ifndef TUTORIALSCREEN2_HPP
#define TUTORIALSCREEN2_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen2 : public IScreen {
    public:
        TutorialScreen2(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen2() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 