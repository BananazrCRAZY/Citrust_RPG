#ifndef VICTORYSCREEN_HPP
#define VICTORYSCREEN_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class VictoryScreen : public IScreen {
    public:
        VictoryScreen(ScreenManager& manager, int cal);
        ~VictoryScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        
        
    private:
        ScreenManager& manager;
        Texture2D background;
        Button nextButton;
        int calories;
        
};

#endif