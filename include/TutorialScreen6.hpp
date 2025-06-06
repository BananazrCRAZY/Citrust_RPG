#ifndef TUTORIALSCREEN6_HPP
#define TUTORIALSCREEN6_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen6 : public IScreen {
    public:
        TutorialScreen6(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen6() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 