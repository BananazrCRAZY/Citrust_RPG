#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include <memory>
#include <raylib.h>
#include "IScreen.hpp"

using namespace std;

class ScreenManager {
public:
    // Initializes first screen, unique pointer guarantees exactly one owner of screen obj, 
    // cant share sames screen obj from two places
    void SetScreen(unique_ptr<IScreen> screen);
    // Replace with a new screen, deleting the old screen
    void ChangeScreen(unique_ptr<IScreen> screen);
    // Forward update/draw calls
    void Update(const Vector2& mousePos, bool mouseClicked);
    void Draw();

private:
    unique_ptr<IScreen> currentScreen;
};

#endif