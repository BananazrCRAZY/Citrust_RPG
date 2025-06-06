#pragma once
#include <string>
#include <raylib.h>

class Popup {
public:
    Popup(float duration = 2.0f);

    void Show(const std::string& message);
    void Update();
    void Draw();

    bool IsVisible() const;

private:
    std::string message;
    float timer;
    float duration;
    bool visible;
};
