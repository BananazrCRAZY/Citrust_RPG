#ifndef SUSPENSESCREEN_HPP
#define SUSPENSESCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class SuspenseScreen : public IScreen {
    public:
        SuspenseScreen(ScreenManager& manager, bool& exitFlag);
        ~SuspenseScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
        Button nextButton;
};

#endif 