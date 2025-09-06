#pragma once
#include <string>
#include <raylib.h>

using std::string;

class CenterPopup {
public:
    CenterPopup(float duration = 1.8f);

    void show(const string& msg, int size, Color col, Color backCol);
    void Update();
    void Draw();
    bool isVisible();
    void setDuration(float time);

private:
    string message;
    float timer;
    float duration;
    bool visible;
    int fontSize;
    Color fontColor, backing;
};
