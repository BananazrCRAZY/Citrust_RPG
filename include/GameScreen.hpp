#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include <raylib.h>

using namespace std;

class GameScreen : public IScreen {
    public:
        GameScreen(ScreenManager& mgr, bool& exitFlag);
        ~GameScreen() override;
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    private:
        ScreenManager& manager;
        bool& exitGame;
        // Add your textures, game state, etc. here
};

#endif
