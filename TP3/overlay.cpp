#include "overlay.h"
#include "raylib.h"

Overlay::Overlay(int width, int height, Resources& resources)
    : _width{width}
    , _height{height}
    , _resources{resources}
{}

void Overlay::renderFps(int fps) 
{
    DrawFPS(40, 40);
    if(GetFPS() < 60)
    {
        Rectangle alert{40, 0, 40, 40 };
        Color c{255, 0, 0, 255};
        DrawRectangleRec(alert, c);
    }
}
