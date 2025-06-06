#ifndef ISCREEN_HPP
#define ISCREEN_HPP

#include <raylib.h>

using namespace std;

class IScreen {
public:
    virtual ~IScreen();
    virtual void Update(const Vector2& mousePos, bool mouseClicked) = 0;
    virtual void Draw() = 0;
};

#endif