#ifndef TUTORIALSCREEN5_HPP
#define TUTORIALSCREEN5_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen5 : public IScreen {
    public:
        TutorialScreen5(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen5() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 