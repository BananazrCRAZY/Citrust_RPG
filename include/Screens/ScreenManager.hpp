#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <memory>
#include <raylib.h>
#include "include/Global.hpp"
#include "IScreen.hpp"
#include "include/Objects/Player.h"
#include "include/bossHeaders/Boss.h"
#include "include/Objects/Item.h"
#include "include/Objects/Shop.h"
#include "include/Popups/CenterPopup.hpp"
#include "include/Popups/Popup.hpp"
#include <string>

using namespace std;

class ScreenManager {
public:
    ScreenManager();
    ~ScreenManager();
    // Initializes first screen, unique pointer guarantees exactly one owner of screen obj, 
    // cant share sames screen obj from two places
    void PushScreen(unique_ptr<IScreen> newScreen);
    void PopScreen();
    // Replace with a new screen, deleting the old screen
    void ChangeScreen(unique_ptr<IScreen> newScreen);
    // Forward update/draw calls
    void Update(const Vector2& mousePos, bool mouseClicked);
    void Draw();
    void SetPlayerName(const string& name) {playerName = name;}
    const string& GetPlayerName() const {return playerName;}
    void setInput(int buttonInput) { input = buttonInput; }
    int getInput() const { return input; }
    void setPlayer(Player* p) { player = p;}
    Player* getPlayer() const { return player; }
    void setBoss(Boss* b) { boss = b;}
    Boss* getBoss() const { return boss; }
    void setShop(Shop* s) { shop = s; }
    Shop* getShop() { return shop; }
    void setShopItems(Item** arr) { shopItems = arr; }
    Item* getShopItem(unsigned i) const { return shopItems[i]; }
    void setCalories(int& cal) { calories = cal; }
    int getCalories() const { return calories; }
    int& getCaloriesVar() {return calories; }

    std::shared_ptr<Popup> getPopup() const { return popup; }
    void ShowPopup(const std::string& msg); // convenience wrapper
    bool isPopup() { return popup->isVisible(); }

    void AddBossCount(int count) { bossCount += count; }
    void setBossCount(int count) { bossCount = count; }
    int GetBossCount() const { return bossCount; }
private:
    vector<unique_ptr<IScreen>> currentScreens;
    string playerName = "";
    int input = -1;
    Player* player = nullptr;
    Boss* boss = nullptr;
    Shop* shop = nullptr;
    std::shared_ptr<Popup> popup;
    int bossCount = 0;
    Item** shopItems = nullptr;
    int defaultCalories = -10000;
    int& calories;
};

#endif