#ifndef PROLOGUESCREEN1_HPP
#define PROLOGUESCREEN1_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "NameScreen.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class PrologueScreen1 : public IScreen {
    public:
        PrologueScreen1(ScreenManager& manager, bool& exitFlag);
        ~PrologueScreen1() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        
        
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
        Button nextButton;
        
};

#endif