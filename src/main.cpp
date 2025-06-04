#include <raylib.h>
#include <iostream>
#include "include/button.hpp"
#include "include/ScreenManager.hpp"
#include "include/TitleScreen.hpp"
#include "include/NameScreen.hpp"

using namespace std;

int main() {   
    // Setup!
    InitWindow(1600, 900, "Orange Game");          // window length 1920 x 1080
    SetTargetFPS(60);
    bool exitGame = false;
    ScreenManager screenManager;

    // Boot into title screen
    screenManager.SetScreen(make_unique<TitleScreen>(screenManager, exitGame));

    // Game Loop: keep running while window isn't closed and exitGame bool isn't flagged
    while ((WindowShouldClose() == false) && (exitGame == false)) {

        // Notes current mouse position and if mouse is pressed
        Vector2 mousePosition = GetMousePosition();
        bool mousePressed = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        screenManager.Update(mousePosition, mousePressed);

        BeginDrawing();
        ClearBackground(BLACK);
        screenManager.Draw();
        EndDrawing();

    }
    CloseWindow();

}