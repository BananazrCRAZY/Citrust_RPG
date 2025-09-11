#include "include/Popups/ItemPopup.hpp"
#include <iostream>
#include <raylib.h>

using namespace std;

ItemPopup::ItemPopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath, unsigned index, ScreenManager& m, const char *secondaryButtonImage) : 
    IndefinitePopup(popupPosition, popupSize, buttonPosition, buttonScale, imagePath),
    itemIndex(index),
    manager(m),
    icon("", {700, 200}, 200, 200),
    secondButton(secondaryButtonImage, {900, 600}, .8),
    itemLines(0),
    effectLines(0),
    maxWidth(box.width - 50),
    needToUpdateDesc(true)
{
    itemDesc[0] = "";
    itemDesc[1] = "";
    itemDesc[2] = "";
    effectDesc[0] = "";
    effectDesc[1] = "";
    effectDesc[2] = "";
}

void ItemPopup::Draw() {
    IndefinitePopup::Draw();
    secondButton.Draw();
    icon.Draw();
}

unsigned ItemPopup::getIndex() const {
    return itemIndex;
}

void ItemPopup::reshapeMsg(string text, string (&arr)[3], int& lines, int fsize) {
    arr[0] = "";
    arr[1] = "";
    arr[2] = "";
    lines = 0;

    int msgWidth = MeasureText(text.c_str(), fsize);
    if (msgWidth >= maxWidth) {
        int charCount = 0;
        for (int i = 0; i < text.length(); i++) {
            int currentWidth = MeasureText(arr[lines].c_str(), fsize);
            if (currentWidth > (maxWidth - 50) && text[i] == ' ') {
                lines++;
                charCount = 0;
            } else {
                arr[lines] += text[i];
            }
            charCount++;
        }
    } else arr[0] = text;

    lines++;

    if (lines > 3) {
        std::cerr << "Error: ItemPopup, reshapeMsg(), lines > 3";
        exit(1);
    }
}