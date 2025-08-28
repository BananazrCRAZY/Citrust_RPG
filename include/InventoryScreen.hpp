#ifndef INVENTORYSCREEN_HPP
#define INVENTORYSCREEN_HPP

#include "InventoryPopup.hpp"
#include "IScreen.hpp"
#include "Player.h"
#include "ScreenManager.hpp"
#include "SolidButton.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class InventoryScreen : public IScreen {
    public:
        InventoryScreen(ScreenManager& manager, bool& exitFlag, Player* p);
        ~InventoryScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Player* player;
        SolidButton* buttons[6];
        Button backButton;
        Texture2D background;
        InventoryPopup menu;
};

#endif 