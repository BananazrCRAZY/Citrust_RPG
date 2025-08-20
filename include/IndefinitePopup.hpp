#pragma once
#include "include/button.hpp"
#include <string>
#include <raylib.h>

using std::string;

class IndefinitePopup {
public:
    IndefinitePopup(Vector2 popupPosition, Vector2 popupSize, Vector2 buttonPosition, float buttonScale, const char *imagePath);

    void Show(const string& message);
    void Update(const Vector2& mousePos, bool mouseClicked);
    void Draw();

protected:
    Vector2 position;
    Vector2 size;
    bool visible;
    Button cancelButton;
    Rectangle box;
};
