#include "Entity.h"

// PRIVATE HELPER METHODS

Entity::~Entity()
{
    delete _hitBox;
}

float Entity::getCenterX() const
{
    return _x + _w / 2.f;
}

float Entity::getCenterY() const
{
    return _y + _h / 2.f;
}

void Entity::checkBounds()
{
    if (this->getCenterX() < 0)
    {
        _x = _screenW - _w / 2;
    }
    else if (this->getCenterX() > _screenW)
    {
        _x = 0 - _w / 2;
    }
    if (this->getCenterY() < 0)
    {
        _y = _screenH - _h / 2;
    }
    else if (this->getCenterY() > _screenH)
    {
        _y = 0 - _h / 2;
    }
}

Entity::Entity(float x, float y, int w, int h, int screenW, int screenH)
    : _x{x}, _y{y}
    , _w{w}, _h{h}
    , _screenW{screenW}
    , _screenH{screenH}
    , _hitBox{}
{}

HitBox& Entity::getHitBox() const
{
    return *_hitBox;
}

float Entity::getX() const
{
    return _x;
}

float Entity::getY() const
{
    return _y;
}
