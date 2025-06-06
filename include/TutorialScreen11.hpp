#ifndef TUTORIALSCREEN11_HPP
#define TUTORIALSCREEN11_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class TutorialScreen11 : public IScreen {
    public:
        TutorialScreen11(ScreenManager& manager, bool& exitFlag);
        ~TutorialScreen11() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
};

#endif 