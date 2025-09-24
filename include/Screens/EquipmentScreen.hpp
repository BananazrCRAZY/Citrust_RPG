#ifndef EQUIPMENTSCREEN_HPP
#define EQUIPMENTSCREEN_HPP

#include "include/Popups/EquipPopup.hpp"
#include "include/Popups/StatsPopup.hpp"
#include "include/Buttons/InventoryButton.hpp"
#include "IScreen.hpp"
#include "include/Objects/Player.h"
#include "ScreenManager.hpp"
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
        Button statsButton;
        StatsPopup statsMenu;

        // variables for scroll feature
        float scrollOffset = 0.0f;
        const int maxPerRow = 8;
        const int maxVisibleRows = 3;
        const int unequippedXStart = 265;
        const int itemWidth = 125;
        const int itemHeight = 125;
        const int unequippedSpacingX = 160;
        const int unequippedSpacingY = 200;
        Rectangle scrollPanel = {unequippedXStart, 320, maxPerRow * unequippedSpacingX, maxVisibleRows * unequippedSpacingY - (unequippedSpacingY - itemHeight)};

};

#endif 