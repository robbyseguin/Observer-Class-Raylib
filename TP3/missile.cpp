#include "missile.h"

#include <cmath>
#include "raylib.h"
#include "Code_Utilities_Light_v2.h"

#include "laser.h"
#include "player.h"
#include "particle.h"
#include "debug.h"

constexpr float LIFETIME = 3.0f; // (in seconds)
constexpr float TURN_SPEED = 2.0f; // in rad/sec
constexpr int NUM_PARTICLES = 10;
constexpr int WIDTH = 12;
constexpr int HEIGHT = 20;

// PRIVATE HELPER FUNCTIONS

void Missile::spawnExplosion()
{
    for (int i = 0; i < NUM_PARTICLES; ++i)
    {
        _entities.push_back(new Particle(
            // Center coords on ship
            _x + static_cast<float>(_w) / 2.0f,
            _y + static_cast<float>(_h) / 2.0f,
            // Random vx and vy between -10 and 10
            static_cast<float>(BdB::randInt(-10, 10)),
            static_cast<float>(BdB::randInt(-10, 10)),
            // Random lifetime between 2 and 4 seconds
            static_cast<float>(BdB::randInt(2, 4)),
            // Random type from 1 to 3
            BdB::randInt(1, 3),
            _screenW,
            _screenH
        ));
    }
}

// PUBLIC FUNCTIONS

Missile::Missile(float x, float y, float speed, float angle, int playerNum,
                 int screenW, int screenH, EntityList& entities)
    : Entity(x, y, WIDTH, HEIGHT, screenW, screenH)
    , _entities{entities}
    , _speed{speed}
    , _angle{angle}
    , _timeAlive{0.0f}
    , _playerNum{playerNum}
    , _alive{true}
{
    _hitBox = new HitBox(-_w / 2, -_h / 2, _w, _h);
}

void Missile::update(float delta)
{
    _timeAlive += delta;

    // Ensure angle is always within (-PI, PI)
    if (_angle < -PI)
    {
        _angle = _angle + PI * 2;
    }
    else if (_angle > PI)
    {
        _angle = _angle - PI * 2;
    }

    // Steer towards the enemy player
    for (unsigned int i = 0; i < _entities.size(); i++)
    {
        Entity* entity = _entities[i];
        // Find enemy position
        if (entity->getId() == 0 && ((Player*)entity)->getPlayerNum() != _playerNum)
        {
            float enemy_x = entity->getX();
            float enemy_y = entity->getY();

            float angle_between = atan2(enemy_y - _y, enemy_x - _x);

            if (_angle > angle_between)
            {
                if (_angle - angle_between < PI)
                {
                    _angle -= TURN_SPEED * delta;
                }
                else
                {
                    _angle += TURN_SPEED * delta;
                }
            }
            else
            {
                if (angle_between - _angle < PI)
                {
                    _angle += TURN_SPEED * delta;
                }
                else
                {
                    _angle -= TURN_SPEED * delta;
                }
            }
        }
    }

    // Apply change in x and y directions
    _x += delta * _speed * cosf(_angle);
    _y += delta * _speed * sinf(_angle);

    checkBounds();

    _hitBox->updatePos(_x, _y, _angle);
}

void Missile::render(Resources* resources, float delta)
{
    // Render hitbox corners if enabled from debug.h
#ifdef DEBUG_RENDER_HITBOX_CORNERS
    _hitBox->renderCorners();
#endif

    // Choose texture (changes missile color)
    const std::string texName = (_playerNum == 1) ? "missile1" : "missile2";
    const Texture2D& texture = resources->getTexture(texName, 1);

    const Rectangle dst = {
        _x,
        _y,
        (float)texture.width,
        (float)texture.height
    };

    // Convert angle to degrees for SDL_RenderCopyEx()
    const float rect_angle = _angle / PI * 180 + 90;
    DrawTexturePro(
        texture, //texture, 
        {0.0f, 0.0f, (float)texture.width, (float)texture.height},
        dst,
        {static_cast<float>(texture.width) / 2, static_cast<float>(texture.height) / 2},
        rect_angle,
        WHITE);
}

bool Missile::isAlive()
{
   // return _timeAlive < LIFETIME && _alive;
    return true;
}

int Missile::getId()
{
    return 1;
}

bool Missile::collides()
{
    return true;
}

bool Missile::doesCollide(int id)
{
    return id == 4;
}

void Missile::collideEntity(Entity& entity)
{
    switch (entity.getId())
    {
    case 0:
        if (((Player*)&entity)->getPlayerNum() != _playerNum)
        {
            _alive = false;
            this->spawnExplosion();
        }
        break;
    case 4:
        if (((Laser*)&entity)->getPlayerNum() != _playerNum)
        {
            _alive = false;
            this->spawnExplosion();
        }
        break;
    default:
        break;
    }
}

int Missile::getPlayerNum()
{
    return _playerNum;
}
