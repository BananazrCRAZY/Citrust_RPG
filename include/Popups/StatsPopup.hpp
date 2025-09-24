#pragma once
#include "include/Buttons/button.hpp"
#include "include/bossHeaders/Boss.h"
#include "IndefinitePopup.hpp"
#include "include/Objects/Player.h"
#include "include/Screens/ScreenManager.hpp"
#include "include/Buttons/TextButton.hpp"
#include "include/Buttons/SolidButton.hpp"
#include <string>
#include <raylib.h>

using std::string;

class StatsPopup : public IndefinitePopup {
    Boss* boss;
    Player* player;
    TextButton playerStatsButton;
    TextButton bossStatsButton;
    bool isShowingPlayerStats;
    int playerTurn;
    bool needToUpdateEffects;
    TextButton* playerEffects[20];
    TextButton* bossEffects[6];
    unsigned playerEffectsSize, bossEffectsSize;
    int mainPopupFontSize = 30;
    // int playerXStart, bossXStart;

    float scrollOffset = 0.0f;
    const int maxVisibleRows = 4;
    const float statusWidth = 400;
    const float statusHeight = 75;
    const int statusSpacingY = 80;
    const float yStarting = 460;
    Rectangle scrollPanel;

    float statsScrollOffset = 0.0f;
    const int statsMaxVisibleRows = 4;
    const float statsHeight = 20;
    const int statsSpacingY = 40;
    const int statsXOffset = 35;
    const int statsDistanceFromBorder = 10;
    float statsYStarting;
    const int numberOfStatRows = 8;
    Rectangle statsScrollPanel;

    void updatePosition(float newXPos);
    void deleteEffectArrays();

    public:
        StatsPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            Boss* b, Player* p);
        ~StatsPopup();
        void Update(const Vector2& mousePos, bool mouseClicked, ScreenManager& manager);
        void Draw();
        void toggleVisible();
};
