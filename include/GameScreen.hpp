#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP

#include "IScreen.hpp"
#include "ScreenManager.hpp"
#include "Game.h"
#include <raylib.h>
#include <string>

using namespace std;

class GameScreen : public IScreen {
    public:
        GameScreen(ScreenManager& mgr, bool& exitFlag, const string& savePath);
        ~GameScreen() override;
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    private:
        ScreenManager& manager;
        bool& exitGame;
        // Add your textures, game state, etc. here
        Game* game;
        bool gameStarted;
};

#endif
