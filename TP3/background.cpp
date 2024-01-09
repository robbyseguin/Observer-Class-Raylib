#include "background.h"

#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

using namespace std;

Background::Background(int width, int height)
    : _width{width}
    , _height{height}
{}

void Background::render() 
{
    Color c{ _r, _g, _b, 255 };
    ClearBackground(c);
}

void Background::changeColor() 
{
    _r = BdB::randInt(25);
    _g = BdB::randInt(25);
    _b = BdB::randInt(25);
}

void Background::notify(Event evt)
{
    if (evt == Event::SHIP_DESTROYED)
    {
        cout << "Change Color" << endl;
        changeColor();
    }
}
