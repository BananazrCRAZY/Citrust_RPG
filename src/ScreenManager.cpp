#include "include/ScreenManager.hpp"

using namespace std;

ScreenManager::~ScreenManager() {
        currentScreens.clear();
}


// completely replace whatever was on the stack with new screen, clearing vector and pushes 1 IScreen
void ScreenManager::ChangeScreen(unique_ptr<IScreen> newScreen) {
    currentScreens.clear();
    if (newScreen) {
        currentScreens.push_back(move(newScreen));
    }
}

// pushes 1 IScreen on top of existing stack, a pause of sort, screen underneath still exists
void ScreenManager::PushScreen(unique_ptr<IScreen> newScreen) {
    if (newScreen) {
        currentScreens.push_back(move(newScreen));
    }
}

// removes topmost screen
void ScreenManager::PopScreen() {
    if (!currentScreens.empty()) {      // safety rail
        currentScreens.pop_back();
    }
}

// on each frame, call update on topmost screen
void ScreenManager::Update(const Vector2& mousePos, bool mouseClicked) {
    if (!currentScreens.empty()) {
        currentScreens.back()->Update(mousePos, mouseClicked);
    }
}

// on each frame, call update on topmost screen
void ScreenManager::Draw() {
    if (!currentScreens.empty()) {
        currentScreens.back()->Draw();
    }
}
