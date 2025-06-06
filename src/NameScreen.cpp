#include "include/NameScreen.hpp"
#include "include/GameScreen.hpp"
#include "include/TitleScreen.hpp"
#include "include/PrologueScreen1.hpp"
#include <iostream>

using namespace std;

NameScreen::NameScreen(ScreenManager& mgr, bool& exitFlag) : manager(mgr), exitGame(exitFlag), nextButton("Graphics/nextButton.png",{1200,680}, 1.6)
, inputText(""), textBox({1000, 270, 250, 60}), textBoxActive(false), letterCount(0) {

    Image backgroundImage = LoadImage("Graphics/NameScreen.png");
    ImageResize(&backgroundImage, 1600, 900);

    // Converts image into texture
    background = LoadTextureFromImage(backgroundImage);

    // Deletes image from heap as it is no longer needed
    UnloadImage(backgroundImage);
}

NameScreen::~NameScreen() {
    UnloadTexture(background);
}

void NameScreen::Update(const Vector2& mousePos, bool mouseClicked) {
    
    // clicks to activate textbox
    if (CheckCollisionPointRec(mousePos, textBox) && mouseClicked) {
        textBoxActive = true;
    } else if (mouseClicked) {
        textBoxActive = false;
    }

    // Checks for input and backspace when text box is active, saving it
    if (textBoxActive) {
        int key = GetCharPressed(); // Get char pressed, call it multiple times for chars queued, returns 0 when the queue is empty from raylib.h
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (letterCount < maxChars)) {      // Range of printable and acceptable ASCII values: 32 - 125
                inputText += static_cast<char>(key);                            // Add char of the ascii value into inputText bit by bit! cs61 ref hehe
                letterCount++;
            }
            key = GetCharPressed();
        }

        // Check for backspace,
        if (IsKeyPressed(KEY_BACKSPACE) && !inputText.empty()) {
            inputText.pop_back();
            letterCount--;
        }
    }

    if (nextButton.isPressed(mousePos, mouseClicked)) {
        manager.SetPlayerName(inputText);
    }
}

void NameScreen::Draw() {
    DrawTexture(background, 0, 0, WHITE);
    nextButton.Draw();

    Color borderColor;
    if (textBoxActive) {
        borderColor = RED;
    } else {
        borderColor = GRAY;
    }

    //DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color)
    DrawRectangleLinesEx(textBox, 1, borderColor);

    //DrawText(const char *text, int posX, int posY, int fontSize, Color color)
    DrawText(inputText.c_str(), textBox.x + 10, textBox.y + 13, 55, BLACK);
}

const string& NameScreen::GetInputText() const {
    return inputText;
}