#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <memory>
#include <raylib.h>
#include "IScreen.hpp"
#include "Player.h"
#include "Boss.h"
#include "Popup.hpp"
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
    Player* getPlayer() { return player; }
    void setBoss(Boss* b) { boss = b;}
    Boss* getBoss() { return boss; }

    std::shared_ptr<Popup> getPopup() const { return popup; }
    void ShowPopup(const std::string& msg); // convenience wrapper

private:
    vector<unique_ptr<IScreen>> currentScreens;
    string playerName = "";
    int input = -1;
    Player* player = nullptr;
    Boss* boss = nullptr;
    std::shared_ptr<Popup> popup;
};

#endif