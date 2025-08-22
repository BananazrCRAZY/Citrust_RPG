#ifndef EQUIPMENTSCREEN_HPP
#define EQUIPMENTSCREEN_HPP

#include "EquipPopup.hpp"
#include "InventoryButton.hpp"
#include "IScreen.hpp"
#include "Player.h"
#include "ScreenManager.hpp"
#include "UnequipPopup.hpp"
#include <raylib.h>
#include <memory>

using namespace std;

class EquipmentScreen : public IScreen {
    public:
        EquipmentScreen(ScreenManager& manager, bool& exitFlag, Player* p);
        ~EquipmentScreen() override;
    
        void Update(const Vector2& mousePos, bool mouseClicked) override;
        void Draw() override;
    
    private:
        ScreenManager& manager;
        bool& exitGame;
        Player* player;
        InventoryButton** equipped;
        InventoryButton** unequipped;
        unsigned unequippedSize;
        Button backButton;
        Texture2D background;
        EquipPopup equipMenu;
};

#endif 