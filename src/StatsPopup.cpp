#include "include/Popups/StatsPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

StatsPopup::StatsPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, Boss* b, Player* p) : 
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
    playerXStart(position.x)
{
    scrollPanel = {position.x + 35, yStarting - statusSpacingY + statusHeight, (float)statusWidth + 30, (float)maxVisibleRows * statusSpacingY + 5};

    bossXStart = 1600 - playerXStart - size.x;
}

StatsPopup::~StatsPopup() {
    deleteEffectArrays();
}

void StatsPopup::Update(const Vector2& mousePos, bool mouseClicked, ScreenManager& manager) {
    if (!visible) return;
    if (cancelButton.isPressed(mousePos, mouseClicked)) {
        deleteEffectArrays();
        scrollOffset = 0;
        isShowingPlayerStats = true;
        visible = false;
        return;
    }

    if (!isShowingPlayerStats) {
        boss = manager.getBoss();
        if (playerStatsButton.isPressed(mousePos, mouseClicked)) {
            isShowingPlayerStats = true;
            updatePosition(playerXStart);
            playerStatsButton.setColor(LIGHTGRAY);
            bossStatsButton.setColor(GRAY);
            player = manager.getPlayer();
        }
    }
    
    if (isShowingPlayerStats) {
        player = manager.getPlayer();
        if (bossStatsButton.isPressed(mousePos, mouseClicked)) {
            isShowingPlayerStats = false;
            updatePosition(bossXStart);
            playerStatsButton.setColor(GRAY);
            bossStatsButton.setColor(LIGHTGRAY);
            boss = manager.getBoss();
        }
    }

    if (needToUpdateEffects) {
        if (isShowingPlayerStats) {
            for (unsigned i = 0; i < player->getNumberOfEffects(); i++) {
                string text;
                if (player->getEffect(i)->getTurns() < 0) text = player->getEffect(i)->getName();
                else text = player->getEffect(i)->getName() + "  (" + to_string(player->getEffect(i)->getTurns()) + ")";
                playerEffects[i] = new TextButton({(float)playerXStart + 50, yStarting + statusSpacingY * playerEffectsSize},
                    {statusWidth, statusHeight}, text, WHITE, 20);
                playerEffectsSize++;
            }
            for (unsigned i = playerEffectsSize; i < 20; i++) playerEffects[i] = nullptr;
        } else {
            for (unsigned i = 0; i < boss->getNumberOfEffects(); i++) {
                string text;
                if (boss->getEffect(i)->getTurns() < 0) text = boss->getEffect(i)->getName();
                else text = boss->getEffect(i)->getName() + "  (" + to_string(boss->getEffect(i)->getTurns()) + ")";
                bossEffects[i] = new TextButton({(float)bossXStart + 50, yStarting + statusSpacingY * bossEffectsSize}, 
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
    bossStatsButton.Draw();

    string name;
    if (isShowingPlayerStats) name = player->getName();
    else name = boss->getName();
    int textWidthName = MeasureText(name.c_str(), 30);
    DrawText(name.c_str(), box.x + (box.width - textWidthName)/2, box.y + 110, 40, BLACK);

    string hp = "HP: ";
    if (isShowingPlayerStats) hp += to_string(player->getHp()) + " / " + to_string(player->getMaxHp());
    else hp += "??? / ???";
    DrawText(hp.c_str(), box.x + 25, box.y + 180, 20, BLACK);

    string atk = "ATK: ";
    if (isShowingPlayerStats) atk += to_string(player->getAttack());
    else atk += to_string(boss->getAttack());
    DrawText(atk.c_str(), box.x + 25, box.y + 220, 20, BLACK);

    string def = "DEF: ";
    if (isShowingPlayerStats) def += to_string(player->getDefense());
    else def += to_string(boss->getDefense());
    DrawText(def.c_str(), box.x + (box.width / 2), box.y + 220, 20, BLACK);

    string arts = "ARTS: ";
    if (isShowingPlayerStats) arts += to_string(player->getArts());
    else arts += to_string(boss->getArts());
    DrawText(arts.c_str(), box.x + 25, box.y + 260, 20, BLACK);

    string res = "RES: ";
    if (isShowingPlayerStats) res += to_string(player->getRes());
    else res += to_string(boss->getRes());
    res += "%";
    DrawText(res.c_str(), box.x + (box.width / 2), box.y + 260, 20, BLACK);

    string critR = "CRT RT: ";
    if (isShowingPlayerStats) critR += to_string(player->getCritRate());
    else critR += to_string(boss->getCritRate());
    critR += "%";
    DrawText(critR.c_str(), box.x + 25, box.y + 300, 20, BLACK);

    string critD = "CRT DMG: ";
    if (isShowingPlayerStats) critD += to_string(player->getCritDmg());
    else critD += to_string(boss->getCritDmg());
    critD += "%";
    DrawText(critD.c_str(), box.x + (box.width / 2), box.y + 300, 20, BLACK);   

    string effects = "EFFECTS:";
    DrawText(effects.c_str(), box.x + 25, box.y + 350, 20, BLACK);

    DrawRectangleLinesEx(scrollPanel, 3, DARKGRAY);

    if (!needToUpdateEffects) {
        BeginScissorMode(scrollPanel.x, scrollPanel.y, scrollPanel.width, scrollPanel.height);

        if (isShowingPlayerStats) {
            for (unsigned i = 0; i < playerEffectsSize; i++) {
                // offset by scroll
                playerEffects[i]->setButtonYPos(yStarting + i * statusSpacingY + scrollOffset);
                playerEffects[i]->Draw();
            }
        } else {
            for (unsigned i = 0; i < bossEffectsSize; i++) {
                // offset by scroll
                bossEffects[i]->setButtonYPos(yStarting + i * statusSpacingY + scrollOffset);
                bossEffects[i]->Draw();
            }
        }

        EndScissorMode();
    }
}

void StatsPopup::showStats() {
    visible = true;
}

void StatsPopup::updatePosition(float newXPos) {

}

void StatsPopup::deleteEffectArrays() {
    for (unsigned i = 0; i < playerEffectsSize; i++) delete playerEffects[i];
    for (unsigned i = 0; i < bossEffectsSize; i++) delete bossEffects[i];
    playerEffectsSize = 0;
    bossEffectsSize = 0;
    needToUpdateEffects = true;
}