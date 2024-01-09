#include "laser.h"

#include <cmath>
#include "raylib.h"

#include "resources.h"
#include "player.h"
#include "missile.h"
#include "debug.h"

constexpr float LIFETIME = 1.0f; // (in seconds)

constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;

// PUBLIC FUNCTIONS

Laser::Laser(float x, float y, float speed, float angle, int player_num,
             int screenW, int screenH, EntityList& entities)
    : Entity(x, y, WIDTH, HEIGHT, screenW, screenH)
      , _entities{entities}
      , _speed{speed}
      , _angle{angle}
      , _timeAlive{0.0f}
      , _playerNum{player_num}
      , _alive{true}
{
    _hitBox = new HitBox(-_w / 2, -_h / 2, _w, _h);
}

void Laser::update(float delta)
{
    _timeAlive += delta;

    // Apply change in x and y directions
    _x += delta * _speed * cosf(_angle);
    _y += delta * _speed * sinf(_angle);

    checkBounds();

    _hitBox->updatePos(_x, _y, _angle);
}

void Laser::render(Resources* resources, float delta)
{
    // Render hitbox corners if enabled from debug.h
#ifdef DEBUG_RENDER_HITBOX_CORNERS
    _hitBox->renderCorners();
#endif

    // Choose texture (changes missile color)
    const std::string texName = (_playerNum == 1) ? "laser1" : "laser2";
    const Texture2D& texture = resources->getTexture(texName, 1);

    const Rectangle src = {
        0.0f, 0.0f,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    const Rectangle dst = {
        _x,
        _y,
        static_cast<float>(texture.width),
        static_cast<float>(texture.height)
    };

    const Vector2 origin = {
        static_cast<float>(texture.width) / 2,
        static_cast<float>(texture.height) / 2
    };

    const float rect_angle = _angle / PI * 180 + 90;
    DrawTexturePro( texture, src, dst, origin, rect_angle, WHITE);
}

bool Laser::isAlive()
{
    return _timeAlive < LIFETIME && _alive;
}

int Laser::getId()
{
    return 4;
}

// Lasers don't check for collisions
bool Laser::collides() { return false; }

bool Laser::doesCollide(int id) { return false; }

void Laser::collideEntity(Entity& entity)
{
    switch (entity.getId())
    {
    case 0:
        if (dynamic_cast<Player*>(&entity)->getPlayerNum() != _playerNum)
        {
            _alive = false;
        }
        break;
    case 1:
        if (dynamic_cast<Missile*>(&entity)->getPlayerNum() != _playerNum)
        {
            _alive = false;
        }
        break;
    default:
        break;
    }
}

int Laser::getPlayerNum() const
{
    return _playerNum;
}
