#include "include/ScreenManager.hpp"

using namespace std;

void ScreenManager::SetScreen(unique_ptr<IScreen> screen) {
    currentScreen = move(screen);       // transfers ownership of the ptr from one to another
}

void ScreenManager::ChangeScreen(unique_ptr<IScreen> screen) {
    currentScreen = move(screen);
}

void ScreenManager::Update(const Vector2& mousePos, bool mouseClicked) {
    // null check before using Update()
    if (currentScreen) {
        currentScreen->Update(mousePos, mouseClicked);
    }
}

void ScreenManager::Draw() {
    // null check before using Draw()
    if (currentScreen) {
        currentScreen->Draw();
    }
}