// #ifndef NAMESCREEN_HPP
// #define NAMESCREEN_HPP

// #include "IScreen.hpp"
// #include "ScreenManager.hpp"
// #include "button.hpp"
// #include <raylib.h>
// #include <memory>

// using namespace std;

// class NameScreen : public IScreen {
//     public:
//         NameScreen(ScreenManager& manager, bool& exitFlag);
//         ~NameScreen() override;
    
//         void Update(const Vector2& mousePos, bool mouseClicked) override;
//         void Draw() override;
    
//     private:
//         ScreenManager& manager;
//         bool& exitGame;
//         Texture2D background;
//         Button nextButton;
// };

// #endif 

#ifndef NAMESCREEN_HPP
#define NAMESCREEN_HPP

#include <string>
#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "button.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class NameScreen : public IScreen {
    public:
        NameScreen(ScreenManager& manager, bool& exitFlag);
        ~NameScreen() override;

        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
        const string& GetInputText() const;

    private:
        ScreenManager& manager;
        bool& exitGame;
        Texture2D background;
        Button nextButton;

        string inputText;
        Rectangle textBox;
        bool textBoxActive;
        int letterCount;
        const int maxChars = 20;
};

#endif