#ifndef LOADSCREEN_HPP
#define LOADSCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "include/Buttons/button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class LoadScreen : public IScreen {
    public:
        LoadScreen(ScreenManager& manager, bool& exitFlag);
        ~LoadScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Button saveButton1;
        Button saveButton2;
        Button saveButton3;
        Button trashButton;
        Button backButton;
        Rectangle trashBorder;
        Texture2D background;
        bool deleteSave;
};

#endif