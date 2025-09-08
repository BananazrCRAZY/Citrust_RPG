#include "include/Screens/AppleBossScreen.hpp"
#include "include/Screens/InventoryScreen.hpp"
#include "include/Objects/Player.h"
#include "include/Buttons/button.hpp"
#include "include/Screens/ScreenManager.hpp"
#include "include/Screens/InterludeScreen.hpp"
#include <iostream>

using namespace std;

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



AppleBossScreen::AppleBossScreen(ScreenManager& mgr, bool& exitFlag, unsigned& cycle)
    : manager(mgr)
    , exitGame(exitFlag)
    , battleCycle(cycle)
    , playerHPButton("Graphics/HPBars/player100HP.png", {600,765}, 0.4)
    , bossHPButton("Graphics/HPBars/boss100HP.png", {400,100}, 0.5)
    , spCounterButton("Graphics/SkillPoints/zeroSP.png", {850,705}, 0.35)
    , skillButton("Graphics/Buttons/skillButton.png", {1210,673}, 0.33)
    , attackButton("Graphics/Buttons/attackButton.png", {1068,710}, 0.31)
    , inventoryButton("Graphics/Buttons/inventoryButton.png", {1270,550}, 0.25)
    , statsButton("Graphics/Buttons/statsButton.png", {180, 275}, .8)
    , menu({800, 75}, {500, 750}, {805, 80}, .5, "Graphics/Buttons/xCloseButton.png", manager.getBoss(), manager.getPlayer())
{
    Image backgroundImage;
    switch (manager.GetBossCount()) {
        case 0:
            backgroundImage = LoadImage("Graphics/BossScreens/AppleBossScreen.png");
            break;
        case 1:
            backgroundImage = LoadImage("Graphics/BossScreens/PearBossScreen.png");
            break;
        case 2:
            backgroundImage = LoadImage("Graphics/BossScreens/StrawberryBossScreen.png");
            break;
        case 3:
            backgroundImage = LoadImage("Graphics/BossScreens/GrapeBossScreen.png");
            break;
        case 4:
            backgroundImage = LoadImage("Graphics/BossScreens/DekoponBossScreen.png");
            break;
        case 5:
            backgroundImage = LoadImage("Graphics/BossScreens/GreenMangoBossScreen.png");
            break;
        case 6:
            backgroundImage = LoadImage("Graphics/BossScreens/RedMangoBossScreen.png");
            break;
        case 7:
            backgroundImage = LoadImage("Graphics/BossScreens/PineappleBossScreen.png");
            break;
        case 8:
            backgroundImage = LoadImage("Graphics/BossScreens/DurianBossScreen.png");
            break;
        case 9:
            backgroundImage = LoadImage("Graphics/BossScreens/WatermelonBossScreen.png");
            break;
        default:
            cerr << "boss load background image error" << endl;
            exit(1);
    }
    
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
    mainPopup.Update();
    if (manager.isPopup()) manager.getPopup()->Update();
    if (statsButton.isPressed(mousePos, mouseClicked)) menu.toggleVisible();

    if (menu.isVisible()) {
        menu.Update(mousePos, mouseClicked, manager);
        return;
    }

    Player* player = manager.getPlayer();  // Access persistent player object
    Boss* boss = manager.getBoss();
    if (boss == nullptr) exit(1);

    int index;
    if (player->getMaxHp() == 0 || player->getHp() == 0) index = 0;
    else {
        double check = 5 * player->getHp() / player->getMaxHp();
        if (check < 1 && check > 0) index = 1;
        else index = check;

        if (index >= 5) index = 5;
        if (index <= 0) index = 0;
        static int lastIndex = -1;
        if (index != lastIndex) {               // doesn't access array index out of bounds
            playerHPButton.SetTexture(playerHPTextures[index], 0.40f);
            lastIndex = index;
        }
    }
    
    int indexBossHp;
    if (boss->getMaxHp() == 0 || boss->getHp() == 0) indexBossHp = 0;
    else {
        double check = 5 * boss->getHp() / boss->getMaxHp();
        if (check < 1 && check > 0) indexBossHp = 1;
        else indexBossHp = check;

        if (indexBossHp >= 5) indexBossHp = 5;
        if (indexBossHp <= 0) indexBossHp = 0;
        static int lastBossIndex = -1;
        if (indexBossHp != lastBossIndex) {
            bossHPButton.SetTexture(bossHPTextures[indexBossHp], 0.50f);
            lastBossIndex = indexBossHp;
        }
    }
    
    int skillPts = player->getRechargeCount();
    if (skillPts > 5) skillPts = 5;
    if (skillPts < 0) skillPts = 0;
    spCounterButton.SetTexture(spTextures[skillPts], 0.35f);

    // player buttons
    if (attackButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(0);
    }

    if (inventoryButton.isPressed(mousePos, mouseClicked)) {
        manager.PushScreen(make_unique<InventoryScreen>(manager, exitGame, player));
    }

    if (skillButton.isPressed(mousePos, mouseClicked)) {
        manager.setInput(1);
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
    statsButton.Draw();

    string hp = to_string(manager.getPlayer()->getHp()) + " / " + to_string(manager.getPlayer()->getMaxHp());
    DrawText(hp.c_str(), 620, 790, 30, BLACK);
    string playerLvl = "LVL " + to_string(manager.getPlayer()->getLevel());
    DrawText(playerLvl.c_str(), 612, 745, 27, BLACK);

    string bossName = manager.getBoss()->getName();
    DrawText(bossName.c_str(), 415, 175, 40, BLACK);
    string bossLvl = "LVL " + to_string(manager.getBoss()->getLevel());
    DrawText(bossLvl.c_str(), 825, 185, 30, BLACK);

    string cycleCount = "CYCLE: " + to_string(battleCycle);
    DrawText(cycleCount.c_str(), 200, 80, 30, BLACK);

    if (manager.isPopup()) manager.getPopup()->Draw();
    if (menu.isVisible()) menu.Draw();
    mainPopup.Draw();
}