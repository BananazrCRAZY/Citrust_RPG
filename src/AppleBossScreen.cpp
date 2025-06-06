#include "include/AppleBossScreen.hpp"
#include "include/InventoryScreen.hpp"
#include "include/Player.h"
#include "include/button.hpp"
#include "include/ScreenManager.hpp"

// Player HP Textures
static const char* playerHPTextures[] = {
    "Graphics/HPBars/zeroHP.png",
    "Graphics/HPBars/player20HP.png",
    "Graphics/HPBars/player40HP.png",
    "Graphics/HPBars/player60HP.png",
    "Graphics/HPBars/player80HP.png",
    "Graphics/HPBars/player100HP.png"
};

// Boss HP Textures
static const char* bossHPTextures[] = {
    "Graphics/HPBars/zeroHP.png",
    "Graphics/HPBars/boss20HP.png",
    "Graphics/HPBars/boss40HP.png",
    "Graphics/HPBars/boss60HP.png",
    "Graphics/HPBars/boss80HP.png",
    "Graphics/HPBars/boss100HP.png"
};

// Skill Point Textures
static const char* spTextures[] = {
    "Graphics/SkillPoints/zeroSP.png",
    "Graphics/SkillPoints/oneSP.png",
    "Graphics/SkillPoints/twoSP.png",
    "Graphics/SkillPoints/threeSP.png",
    "Graphics/SkillPoints/fourSP.png",
    "Graphics/SkillPoints/fiveSP.png"
};



AppleBossScreen::AppleBossScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , playerHPButton("Graphics/HPBars/player100HP.png", {600,765}, 1)
    , bossHPButton("Graphics/HPBars/boss100HP.png", {400,100}, 0.5)
    , spCounterButton("Graphics/SkillPoints/zeroSP.png", {850,705}, 0.35)
    , skillButton("Graphics/skillButton.png", {1210,673}, 0.33)
    , attackButton("Graphics/attackButton.png", {1068,710}, 0.31)
    , inventoryButton("Graphics/inventoryButton.png", {1270,550}, 0.25)
{
    Image backgroundImage = LoadImage("Graphics/BossScreens/AppleBossScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

AppleBossScreen::~AppleBossScreen() {
    UnloadTexture(background);
}

void AppleBossScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    Player* player = manager.getPlayer();  // Access persistent player object
    Boss* boss = manager.getBoss();

    int index = 5 * player->getHp() / player->getMaxHp();
    int indexBossHp = 5 * boss->getHp() / boss->getMaxHp();
    static int lastIndex = -1;
    if (index != lastIndex) {               // doesn't access array index out of bounds
        playerHPButton.SetTexture(playerHPTextures[index], 0.40f);
        bossHPButton.SetTexture(bossHPTextures[indexBossHp], 0.50f);
        lastIndex = index;
    }
    spCounterButton.SetTexture(spTextures[player->getRechargeCount()], 0.35f);

    // Handle popup timer
    if (showPopUp) {
        popupTimer += GetFrameTime();
        if (popupTimer >= popupDuration) {
            showPopUp = false;
        }
    }

    // Trigger popups
    if (attackButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(0);
        ShowPopup("Used Basic Attack");
    }

    if (inventoryButton.isPressed(mousePos, mouseClicked)) {
        manager.PushScreen(make_unique<InventoryScreen>(manager, exitGame));
    }

    if (skillButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(1);
        ShowPopup("Used Special Attack");
    }
}

void AppleBossScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    playerHPButton.Draw();
    bossHPButton.Draw();
    spCounterButton.Draw();
    skillButton.Draw();
    attackButton.Draw();
    inventoryButton.Draw();

    // Draw popup box if active
    if (showPopUp) {
        Rectangle popUpBox = { 800, 600, 400, 80 };
        DrawRectangleRec(popUpBox, LIGHTGRAY);
        DrawRectangleLinesEx(popUpBox, 3, DARKGRAY);

        int textWidth = MeasureText(popupMessage.c_str(), 20);
        DrawText(popupMessage.c_str(), popUpBox.x + (popUpBox.width - textWidth)/2, popUpBox.y + 30, 20, BLACK);
    }

}


void AppleBossScreen::ShowPopup(const string& message) {
    popupMessage = message;
    popupTimer = 0.0f;
    showPopUp = true;
}