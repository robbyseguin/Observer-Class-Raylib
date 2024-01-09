#include "particle.h"

Particle::Particle(float x, float y, float vx, float vy, float lifetime,
                   int type, int screenW, int screenH)
    : Entity(x, y, 4, 4, screenW, screenH)
{
    _timeAlive = 0.0f;
    this->_vx = vx;
    this->_vy = vy;
    this->_lifetime = lifetime;
    this->_type = type;
}

void Particle::update(float delta)
{
    _timeAlive += delta;
    _x += _vx * delta;
    _y += _vy * delta;

    checkBounds();
}

void Particle::render(Resources* resources, float delta)
{
    const float alphaLevel = (_lifetime - _timeAlive) / _lifetime * 255.0f;

    const Texture2D& texture = resources->getTexture("particle", _type);

    const Rectangle dst = {
        0, //(x - texture.width / 2.0f),
        0, //(y - texture.height / 2.0f),
        (float)texture.width,
        (float)texture.height
    };

    Color tint = WHITE;
    tint.a = alphaLevel;

    DrawTextureRec(texture, dst, {_x, _y}, tint);
}

bool Particle::isAlive()
{
    return _timeAlive <= _lifetime;
}

int Particle::getId()
{
    return 2;
}

bool Particle::collides()
{
    return false;
}

bool Particle::doesCollide(int id)
{
    return false;
}

void Particle::collideEntity(Entity& entity)
{
}
