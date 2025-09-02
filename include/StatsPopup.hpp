#pragma once
#include "include/button.hpp"
#include "Boss.h"
#include "include/IndefinitePopup.hpp"
#include "Player.h"
#include "ScreenManager.hpp"
#include "TextButton.hpp"
#include "include/SolidButton.hpp"
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
    int playerXStart, bossXStart;

    float scrollOffset = 0.0f;
    const int maxVisibleRows = 4;
    const float statusWidth = 400;
    const float statusHeight = 75;
    const int statusSpacingY = 80;
    const float yStarting = 460;
    Rectangle scrollPanel;

    void updatePosition(float newXPos);
    void deleteEffectArrays();

    public:
        StatsPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, 
            Boss* b, Player* p);
        ~StatsPopup();
        void Update(const Vector2& mousePos, bool mouseClicked, ScreenManager& manager);
        void Draw();
        void showStats();
};
