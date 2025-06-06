#ifndef PROLOGUESCREEN2_HPP
#define PROLOGUESCREEN2_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "NameScreen.hpp"
#include "PrologueScreen1.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class PrologueScreen2 : public IScreen {
    public:
        PrologueScreen2(ScreenManager& manager, bool& exitFlag);
        ~PrologueScreen2() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        
        
    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
        Button nextButton;
        
};

#endif