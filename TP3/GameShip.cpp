#include "GameShip.h"

#include <raylib.h>
#include <Code_Utilities_Light_v2.h>

using namespace std;
using namespace GS;

GameShip::GameShip()
    : _world {
        Graphics::WIDTH,
        Graphics::HEIGHT,
        _titleManager,
        _graphics.getBackground()
    }
{
    BdB::srandInt(static_cast<int>(time(nullptr)));
}

GameShip::~GameShip() = default;

int GameShip::getClickX() const
{
    return std::clamp(GetMouseX(), 0, Graphics::WIDTH);
}

int GameShip::getClickY() const
{
    return std::clamp(GetMouseY(), 0, Graphics::HEIGHT);
}

void GameShip::handleInput()
{
    _inputs.update();
    _keepPlaying = !_inputs.getQuit();
}

void GameShip::update()
{
    _world.update(_inputs);
    _titleManager.updateTitle();
}

void GameShip::render() const
{
    Graphics::startRender();
    {
        _graphics.clearScreen();

        _graphics.renderEntities(_world.getEntities(), _world.getDelta());
        _graphics.renderOverlay();
    }
    Graphics::endRender();
}
