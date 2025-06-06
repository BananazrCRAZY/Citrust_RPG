#ifndef TUTORIALSCREEN7_HPP
#define TUTORIALSCREEN7_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen7 : public IScreen {
    public:
        TutorialScreen7(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen7() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 