#include "include/StatsPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

StatsPopup::StatsPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, Boss* b, Player* p) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    boss(b),
    player(p),
    playerStatsButton({cancelButton.getXPos() + cancelButton.getXSize() + (cancelButton.getXPos()-position.x), position.y},
        {(size.x - (2 * (cancelButton.getXPos()-position.x) + cancelButton.getXSize()))/2, cancelButton.getYSize()},
        "PLAYER", LIGHTGRAY),
    bossStatsButton({playerStatsButton.getXPos() + playerStatsButton.getXSize(), position.y},
        {playerStatsButton.getXSize(), playerStatsButton.getYSize()},
        "BOSS", GRAY),
    playerTurn(0),
    needToUpdateEffects(true),
    playerXStart(position.x)
{
    scrollPanel = {position.x + 50, 400, (float)statusWidth, (float)maxVisibleRows * statusHeight};

    bossXStart = 1600 - playerXStart - size.x;
}

StatsPopup::~StatsPopup() {
    deleteEffectVectors();
}

void StatsPopup::Update(const Vector2& mousePos, bool mouseClicked, ScreenManager& manager) {
    if (!visible) return;
    if (cancelButton.isPressed(mousePos, mouseClicked)) {
        visible = false;
        isShowingPlayerStats = true;
        needToUpdateEffects = true;
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
            for (unsigned i = 0; i < player->getNumberOfEffects(); i++)
                playerEffects[i] = new TextButton({(float)playerXStart + 50, (float)400 + statusSpacingY * i},
                    {statusWidth, statusHeight}, player->getEffect(i)->getName(), WHITE);
            for (unsigned i = player->getNumberOfEffects(); i < 20; i++) playerEffects[i] = nullptr;
        } else {
            for (unsigned i = 0; i < boss->getNumberOfEffects(); i++)
                bossEffects[i] = new TextButton({(float)bossXStart + 50, (float)400 + statusSpacingY * i}, 
                    {statusWidth, statusHeight}, boss->getEffect(i)->getName(), WHITE);
            for (unsigned i = boss->getNumberOfEffects(); i < 6; i++) bossEffects[i] = nullptr;
        }
    }

    if (player->getTurn() == playerTurn) needToUpdateEffects = false;
    else {
        needToUpdateEffects = true;
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









    
    if (isShowingPlayerStats) for (unsigned i = 0; i <)
}

void StatsPopup::showStats() {
    visible = true;
}

void StatsPopup::updatePosition(float newXPos) {

}

void StatsPopup::deleteEffectVectors() {
    for (unsigned i = 0; i < player->getNumberOfEffects(); i++) delete playerEffects[i];
    for (unsigned i = 0; i < boss->getNumberOfEffects(); i++) delete bossEffects[i];
}