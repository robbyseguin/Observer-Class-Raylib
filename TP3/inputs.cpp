#include "inputs.h"

#include "raylib.h"

Inputs::Inputs()
{
    _quit = false;
}

bool Inputs::checkForQuit() 
{
    return WindowShouldClose();
}

bool Inputs::getQuit() const
{
    return _quit;
}

void Inputs::update() 
{
    // ESC or X button close the game
    if(checkForQuit())
        _quit = true;
}

bool Inputs::isKeyDown(int key) 
{
	return IsKeyDown(key);
}