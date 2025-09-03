#pragma once
#include <string>
#include <raylib.h>

class Popup {
public:
    Popup(float duration = 3.0f);

    void Show(const std::string& message);
    void Update();
    void Draw();

private:
    std::string message;
    float timer;
    float duration;
    bool visible;
};
