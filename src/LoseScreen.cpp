#include "include/Screens/LoseScreen.hpp"

LoseScreen::LoseScreen(ScreenManager& manager) :
    manager(manager),
    exitGameButton("Graphics/Buttons/quitButton.png", {0, 725}, 1.05),
    tryAgainButton("Graphics/Buttons/tryAgainButton.png", {0, 725}, 1.2),
    toTitleScreenButton("Graphics/Buttons/titleScreenButton.png", {0, 725}, 1.2)
{
    Image backgroundImage = LoadImage("Graphics/GeneralScreens/loseScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);

    float centering = 800 - (tryAgainButton.getXSize()/2);
    tryAgainButton.setXPos(centering);

    exitGameButton.setXPos(centering-150-exitGameButton.getXSize());
    toTitleScreenButton.setXPos(centering+150+tryAgainButton.getXSize());
}

LoseScreen::~LoseScreen() {
    UnloadTexture(background);
}

void LoseScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (exitGameButton.isPressed(mousePos, mouseClicked)) manager.setInput(0);
    if (toTitleScreenButton.isPressed(mousePos, mouseClicked)) manager.setInput(1);
    if (tryAgainButton.isPressed(mousePos, mouseClicked)) manager.setInput(2);
}

void LoseScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    exitGameButton.Draw();
    tryAgainButton.Draw();
    toTitleScreenButton.Draw();
}