#pragma once
#include <string>
#include <raylib.h>

using std::string;

class Popup {
public:
    Popup(float duration = 1.0f);

    void Show(const string& message);
    void Update();
    void Draw();
    bool isVisible();

private:
    string message;
    string displayMessage;
    float timer;
    float duration;
    bool visible;
    unsigned index;

    void getDisplayMessage();
};
