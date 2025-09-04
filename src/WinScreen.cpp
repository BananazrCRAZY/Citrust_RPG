#include "include/Screens/WinScreen.hpp"

WinScreen::WinScreen(ScreenManager& manager) :
    manager(manager),
    exitGameButton("Graphics/Buttons/quitButton.png", {725, 350}, 0.7),
    toTitleScreenButton("Graphics/Buttons/titleScreenButton.png", {725, 475}, 0.7)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/winScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

WinScreen::~WinScreen() {
    UnloadTexture(background);
}

void WinScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (exitGameButton.isPressed(mousePos, mouseClicked)) manager.setInput(0);
    if (toTitleScreenButton.isPressed(mousePos, mouseClicked)) manager.setInput(1);
}

void WinScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    exitGameButton.Draw();
    toTitleScreenButton.Draw();
}