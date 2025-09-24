#include "include/Popups/StatsPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

StatsPopup::StatsPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, Boss* b, Player* p, bool usingBossStats) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    boss(b),
    player(p),
    playerStatsButton({cancelButton.getXPos() + cancelButton.getXSize() + (cancelButton.getXPos()-position.x), position.y},
        {(size.x - (2 * (cancelButton.getXPos()-position.x) + cancelButton.getXSize()))/2, cancelButton.getYSize()},
        "PLAYER", LIGHTGRAY, 15),
    bossStatsButton({playerStatsButton.getXPos() + playerStatsButton.getXSize(), position.y},
        {playerStatsButton.getXSize(), playerStatsButton.getYSize()},
        "BOSS", GRAY, 15),
    playerTurn(0),
    needToUpdateEffects(true),
    playerEffectsSize(0),
    bossEffectsSize(0),
    isShowingPlayerStats(true),
    usingBossStats(usingBossStats)
{
    statsYStarting = box.y + 180;
    statsScrollPanel = {position.x + statsXOffset, statsYStarting - 10, box.width - statsXOffset * 2, (float)statsMaxVisibleRows * statsSpacingY};
    scrollPanel = {position.x + statsXOffset, yStarting - statusSpacingY + statusHeight, (float)statusWidth + 30, (float)maxVisibleRows * statusSpacingY + 5};

    if (!usingBossStats) playerStatsButton.setWidth(playerStatsButton.getXSize() + bossStatsButton.getXSize());
}

StatsPopup::~StatsPopup() {
    deleteEffectArrays();
}

void StatsPopup::Update(const Vector2& mousePos, bool mouseClicked, ScreenManager& manager) {
    if (!visible) return;
    if (cancelButton.isPressed(mousePos, mouseClicked)) {
        deleteEffectArrays();
        scrollOffset = 0;
        statsScrollOffset = 0;
        visible = false;
        if (usingBossStats) {
            playerStatsButton.setColor(LIGHTGRAY);
            bossStatsButton.setColor(GRAY);
            isShowingPlayerStats = true;
        } else needToUpdateEffects = true;
        return;
    }

    if (!isShowingPlayerStats) {
        boss = manager.getBoss();
        for (unsigned i = 0; i < bossEffectsSize; i++) {
            // Only check if mouse is inside the visible panel
            if (CheckCollisionPointRec(mousePos, scrollPanel)) {
                if (bossEffects[i]->isPressed(mousePos, mouseClicked)) {
                    mainPopup.show(boss->getEffect(i)->getDescription().c_str(), mainPopupFontSize, BLACK, WHITE);
                    return;
                }
            }
        }
        if (playerStatsButton.isPressed(mousePos, mouseClicked)) {
            isShowingPlayerStats = true;
            // updatePosition(playerXStart);
            playerStatsButton.setColor(LIGHTGRAY);
            bossStatsButton.setColor(GRAY);
            player = manager.getPlayer();
        }
    }

    if (isShowingPlayerStats) {
        player = manager.getPlayer();
        for (unsigned i = 0; i < playerEffectsSize; i++) {
            // Only check if mouse is inside the visible panel
            if (CheckCollisionPointRec(mousePos, scrollPanel)) {
                if (playerEffects[i]->isPressed(mousePos, mouseClicked)) {
                    mainPopup.show(player->getEffect(i)->getDescription().c_str(), mainPopupFontSize, BLACK, WHITE);
                    return;
                }
            }
        }
        if (usingBossStats) {
            if (bossStatsButton.isPressed(mousePos, mouseClicked)) {
                isShowingPlayerStats = false;
                // updatePosition(bossXStart);
                playerStatsButton.setColor(GRAY);
                bossStatsButton.setColor(LIGHTGRAY);
                boss = manager.getBoss();
            }
        }
    }

    if (needToUpdateEffects) {
        for (unsigned i = 0; i < player->getNumberOfEffects(); i++) {
            string text;
            if (player->getEffect(i)->getTurns() < 0) text = player->getEffect(i)->getName();
            else text = player->getEffect(i)->getName() + "  (" + to_string(player->getEffect(i)->getTurns()+1) + ")";
            playerEffects[i] = new TextButton({(float)position.x + 50, yStarting + statusSpacingY * playerEffectsSize},
                {statusWidth, statusHeight}, text, WHITE, 20);
            playerEffectsSize++;
        }
        for (unsigned i = playerEffectsSize; i < 20; i++) playerEffects[i] = nullptr;

        if (usingBossStats) {
            for (unsigned i = 0; i < boss->getNumberOfEffects(); i++) {
                string text;
                if (boss->getEffect(i)->getTurns() < 0) text = boss->getEffect(i)->getName();
                else text = boss->getEffect(i)->getName() + "  (" + to_string(boss->getEffect(i)->getTurns()+1) + ")";
                bossEffects[i] = new TextButton({(float)position.x + 50, yStarting + statusSpacingY * bossEffectsSize}, 
                    {statusWidth, statusHeight}, text, WHITE, 20);
                bossEffectsSize++;
            }
            for (unsigned i = bossEffectsSize; i < 6; i++) bossEffects[i] = nullptr;
        }
        playerTurn = player->getTurn();
    }

    if (player->getTurn() == playerTurn) needToUpdateEffects = false;
    else {
        deleteEffectArrays();
        playerTurn = player->getTurn();
    }

    // Scroll only when mouse is inside the unequipped panel
    if (CheckCollisionPointRec(mousePos, statsScrollPanel)) {
        statsScrollOffset += GetMouseWheelMove() * 30.0f; // scroll speed
    }

    // compute total rows
    float statsMaxScroll = numberOfStatRows * statsSpacingY - statsMaxVisibleRows * statsSpacingY;
    if (statsMaxScroll < 0) statsMaxScroll = 0;

    // clamp
    if (statsScrollOffset > 0) statsScrollOffset = 0;
    if (statsScrollOffset < -statsMaxScroll) statsScrollOffset = -statsMaxScroll;

    // Scroll only when mouse is inside the unequipped panel
    if (CheckCollisionPointRec(mousePos, scrollPanel)) {
        scrollOffset += GetMouseWheelMove() * 30.0f; // scroll speed
    }

    // compute total rows
    int totalRows = 0;
    if (isShowingPlayerStats) totalRows = player->getNumberOfEffects();
    else totalRows = boss->getNumberOfEffects();
    float maxScroll = totalRows * statusSpacingY - maxVisibleRows * statusSpacingY;
    if (maxScroll < 0) maxScroll = 0;

    // clamp
    if (scrollOffset > 0) scrollOffset = 0;
    if (scrollOffset < -maxScroll) scrollOffset = -maxScroll;
}

void StatsPopup::Draw() {
    if (!visible) return;
    IndefinitePopup::Draw();
    playerStatsButton.Draw();
    if (usingBossStats) bossStatsButton.Draw();

    string name;
    if (isShowingPlayerStats) name = player->getName();
    else name = boss->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName) / 2,
        ((playerStatsButton.getYPos() + playerStatsButton.getYSize()) + (statsScrollPanel.y - 30)) / 2 - 25, 45, BLACK);

    string stats = "STATS:";
    DrawText(stats.c_str(), box.x + 25, statsScrollPanel.y - 30, 20, BLACK);

    DrawRectangleLinesEx(statsScrollPanel, 3, DARKGRAY);
    BeginScissorMode(statsScrollPanel.x, statsScrollPanel.y, statsScrollPanel.width, statsScrollPanel.height);

    string hp = "HP: ";
    if (isShowingPlayerStats) hp += to_string(player->getHp()) + " / " + to_string(player->getStat(0));
    else hp += "??? / ???";
    DrawText(hp.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + statsScrollOffset, 20, BLACK);

    string atk = "ATK: ";
    if (isShowingPlayerStats) atk += to_string(player->getStat(1));
    else atk += to_string(boss->getStat(1));
    DrawText(atk.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + statsSpacingY + statsScrollOffset, 20, BLACK);

    string def = "DEF: ";
    if (isShowingPlayerStats) def += to_string(player->getStat(2));
    else def += to_string(boss->getStat(2));
    DrawText(def.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + statsSpacingY + statsScrollOffset, 20, BLACK);

    string arts = "ARTS: ";
    if (isShowingPlayerStats) arts += to_string(player->getStat(3));
    else arts += to_string(boss->getStat(3));
    DrawText(arts.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 2 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string res = "RES: ";
    if (isShowingPlayerStats) res += to_string(player->getStat(4));
    else res += to_string(boss->getStat(4));
    res += "%";
    DrawText(res.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + 2 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string critR = "CRT RT: ";
    if (isShowingPlayerStats) critR += to_string(player->getStat(5));
    else critR += to_string(boss->getStat(5));
    critR += "%";
    DrawText(critR.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 3 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string critD = "CRT DMG: ";
    if (isShowingPlayerStats) critD += to_string(player->getStat(6));
    else critD += to_string(boss->getStat(6));
    critD += "%";
    DrawText(critD.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + 3 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string eva = "EVA: ";
    if (isShowingPlayerStats) eva += to_string(player->getStat(7));
    else eva += to_string(boss->getStat(7));
    DrawText(eva.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 4 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string intel = "INTEL: ";
    if (isShowingPlayerStats) intel += to_string(player->getStat(8));
    else intel += to_string(boss->getStat(8));
    DrawText(intel.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + 4 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string basic = "BASIC DMG: ";
    if (isShowingPlayerStats) basic += to_string(player->getStat(9));
    else basic += to_string(boss->getStat(9));
    basic += "%";
    DrawText(basic.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 5 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string skill = "SKILL DMG: ";
    if (isShowingPlayerStats) skill += to_string(player->getStat(10));
    else skill += to_string(boss->getStat(10));
    skill += "%";
    DrawText(skill.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + 5 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string amp = "DMG AMP: ";
    if (isShowingPlayerStats) amp += to_string(player->getStat(11));
    else amp += to_string(boss->getStat(11));
    amp += "%";
    DrawText(amp.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 6 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string weak = "WEAK: ";
    if (isShowingPlayerStats) weak += to_string(player->getStat(12));
    else weak += to_string(boss->getStat(12));
    weak += "%";
    DrawText(weak.c_str(), box.x + (box.width / 2) + statsDistanceFromBorder, statsYStarting + 6 * statsSpacingY + statsScrollOffset, 20, BLACK);

    string vuln = "VULN: ";
    if (isShowingPlayerStats) vuln += to_string(player->getStat(13));
    else vuln += to_string(boss->getStat(13));
    vuln += "%";
    DrawText(vuln.c_str(), box.x + statsXOffset + statsDistanceFromBorder, statsYStarting + 7 * statsSpacingY + statsScrollOffset, 20, BLACK);
    
    EndScissorMode();

    string effects = "EFFECTS:";
    DrawText(effects.c_str(), box.x + 25, box.y + 350, 20, BLACK);

    DrawRectangleLinesEx(scrollPanel, 3, DARKGRAY);
    if (!needToUpdateEffects) {
        BeginScissorMode(scrollPanel.x, scrollPanel.y, scrollPanel.width, scrollPanel.height);

        if (isShowingPlayerStats) {
            for (unsigned i = 0; i < playerEffectsSize; i++) {
                // offset by scroll
                playerEffects[i]->setYPos(yStarting + i * statusSpacingY + scrollOffset);
                playerEffects[i]->Draw();
            }
        } else {
            for (unsigned i = 0; i < bossEffectsSize; i++) {
                // offset by scroll
                bossEffects[i]->setYPos(yStarting + i * statusSpacingY + scrollOffset);
                bossEffects[i]->Draw();
            }
        }

        EndScissorMode();
    }
}

void StatsPopup::toggleVisible() {
    visible = !visible;
    if (!visible) {
        deleteEffectArrays();
        scrollOffset = 0;
        statsScrollOffset = 0;
        if (usingBossStats) {
            playerStatsButton.setColor(LIGHTGRAY);
            bossStatsButton.setColor(GRAY);
            isShowingPlayerStats = true;
        } else needToUpdateEffects = true;
    }
}

void StatsPopup::deleteEffectArrays() {
    if (isShowingPlayerStats)
        for (unsigned i = 0; i < playerEffectsSize; i++) delete playerEffects[i];
    else
        for (unsigned i = 0; i < bossEffectsSize; i++) delete bossEffects[i];
    playerEffectsSize = 0;
    bossEffectsSize = 0;
    needToUpdateEffects = true;
}