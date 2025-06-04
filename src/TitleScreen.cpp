#include "include/TitleScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/NameScreen.hpp"
#include <iostream>

using namespace std;

TitleScreen::TitleScreen(ScreenManager& mgr, bool& exitFlag)
    : manager(mgr)
    , exitGame(exitFlag)
    , background(LoadTexture("Graphics/titleScreen.png"))
    , startButton("Graphics/newButton.png", {650,300}, 1)
    , loadButton("Graphics/loadButton.png", {650,450}, 1)
    , quitButton("Graphics/quitButton.png", {648,576}, 1)
{}

TitleScreen::~TitleScreen() {
    UnloadTexture(background);
}

void TitleScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    if (startButton.isPressed(mousePos, mouseClicked)) {
        manager.ChangeScreen(make_unique<NameScreen>(manager, exitGame));
        //cout << "hello";

    }
    if (loadButton.isPressed(mousePos, mouseClicked)) {
        // load game logic
        cout << "no";
    }
    if (quitButton.isPressed(mousePos, mouseClicked)) {
        exitGame = true;
    }
}

void TitleScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    startButton.Draw();
    loadButton.Draw();
    quitButton.Draw();
}