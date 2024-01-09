#include "player.h"

#include <cmath>
#include <iostream>
#include "Code_Utilities_Light_v2.h"

#include "missile.h"
#include "laser.h"
#include "particle.h"
#include "ShipPart.h"
#include "debug.h"

using namespace std;

// Time between firing missiles
// *************** Pas de délais entre les missiles, le jeu est plus cool comme ça!
constexpr float MISSILE_DELAY = 0.0f;

// Time between firing lasers
constexpr float LASER_DELAY = 0.2f;
// How many particles are spawned when the ship explodes
constexpr int NUM_PARTICLES = 350;
// Duration between blinks while invincible
constexpr float BLINK_INTERVAL = 0.2f;

constexpr int WIDTH = 36;
constexpr int HEIGHT = 40;

// PRIVATE HELPER FUNCTIONS

void Player::spawnExplosion() const
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

    // Create the 4 fragmented pieces of the ship
    for (int i = 1; i <= 4; ++i)
    {
        _entities.push_back(new ShipPart(
            // Center coords on ship
            _x + _w / 2.0f,
            _y + _h / 2.0f,
            // Random vx and vy between -10 and 10
            static_cast<float>(BdB::randInt(-10, 10)),
            static_cast<float>(BdB::randInt(-10, 10)),
            // Random rot_speed between -30 and 30
            static_cast<float>(BdB::randInt(-30, 30)),
            // Random lifetime between 3 and 4 seconds
            BdB::randInt(3, 4),
            _playerNum,
            i,
            _screenW,
            _screenH
        ));
    }
}

// PUBLIC FUNCTIONS

Player::Player(float x, float y, int player_num, int screen_w, int screen_h,
               EntityList& entities,float invincible_time)
    : Entity(x, y, WIDTH, HEIGHT, screen_w, screen_h)
    , _entities{entities}
    , _vx{}, _vy{}
    , _turnSpeed{3.0f}, _linearAcceleration{300.0f}
    , _maxSpeed{300.0f}
    , _playerNum{player_num}
    , _angle{0}
    , _missileCooldown{0.0f}
    , _laserCooldown{0.0f}
    , _alive{true}
    , _timeAlive{0}
    , _invincibleTime{invincible_time}
    , _hasFired{false}
{
    _hitBox = new HitBox(-_w / 2, -_h / 2, _w, _h);
}

void Player::shootMissile()
{
    if (_missileCooldown == 0)
    {
        _hasFired = true;
        _missileCooldown = MISSILE_DELAY;
        float speed = 400;
        _entities.push_back(new Missile(_x, _y, speed, _angle, _playerNum,
                                        _screenW, _screenH, _entities));
        invoke(Event::MISSILE_SHOT);
        
    }
}

void Player::shootLaser()
{
    if (_laserCooldown == 0)
    {
        _hasFired = true;
        _laserCooldown = LASER_DELAY;
        float speed = 800;
        _entities.push_back(new Laser(_x, _y, speed, _angle, _playerNum,
                                      _screenW, _screenH, _entities));
    }
}

void Player::update(float delta)
{
    _timeAlive += delta;

    // Apply change in x and y directions
    _x += delta * _vx;
    _y += delta * _vy;

    // Enforce speed limit
    if (_vx > _maxSpeed)
        _vx = _maxSpeed;

    if (_vy > _maxSpeed)
        _vy = _maxSpeed;

    if (_vx < -_maxSpeed)
        _vx = -_maxSpeed;

    if (_vy < -_maxSpeed)
        _vy = -_maxSpeed;

    // Timers
    if (_missileCooldown > 0)
    {
        _missileCooldown -= delta;
        if (_missileCooldown < 0)
            _missileCooldown = 0;
    }

    if (_laserCooldown > 0)
    {
        _laserCooldown -= delta;
        if (_laserCooldown < 0)
            _laserCooldown = 0;
    }

    checkBounds();

    _hitBox->updatePos(_x, _y, _angle);
}

void Player::render(Resources* resources, float delta)
{
#ifdef DEBUG_RENDER_HITBOX_CORNERS
    _hitBox->renderCorners();
#endif

    if ((_timeAlive > _invincibleTime || _hasFired) || static_cast<int>(_timeAlive / BLINK_INTERVAL) % 2 == 0)
    {
        const std::string texName = (_playerNum == 1) ? "ship1" : "ship2";
        const Texture2D& texture = resources->getTexture(texName, 1);

        const Rectangle src = {
            0.0f, 0.0f,
            static_cast<float>(texture.width),
            static_cast<float>(texture.height)
        };

        const Rectangle dst = {
            _x, _y,
            static_cast<float>(texture.width),
            static_cast<float>(texture.height)
        };

        const Vector2 origin = {
            static_cast<float>(texture.width) / 2,
            static_cast<float>(texture.height) / 2
        };

        const float rect_angle = _angle / PI * 180 + 90;
        DrawTexturePro(texture, src, dst, origin, rect_angle, WHITE);
    }
}

// TODO: Fix redundancy
void Player::handleInputs(float delta, Inputs& inputs)
{
    // PLAYER 1
    if (_playerNum == 1)
    {
        // Movement Controls
        if (inputs.isKeyDown(KEY_P1_MOVE_UP))
        {
            _vx += delta * _linearAcceleration * cosf(_angle);
            _vy += delta * _linearAcceleration * sinf(_angle);
        }
        else if (inputs.isKeyDown(KEY_P1_MOVE_DOWN))
        {
            _vx -= delta * _linearAcceleration * cosf(_angle);
            _vy -= delta * _linearAcceleration * sinf(_angle);
        }

        if (inputs.isKeyDown(KEY_P1_MOVE_LEFT))
        {
            _angle -= delta * _turnSpeed;
        }
        else if (inputs.isKeyDown(KEY_P1_MOVE_RIGHT))
        {
            _angle += delta * _turnSpeed;
        }

        // Shooting
        if (inputs.isKeyDown(KEY_P1_FIRE_MISSILE))
            shootMissile();

        if (inputs.isKeyDown(KEY_P1_FIRE_LASER))
            shootLaser();
    }

    // PLAYER 2
    if (_playerNum == 2)
    {
        // Movement Controls
        if (inputs.isKeyDown(KEY_P2_MOVE_UP))
        {
            _vx += delta * _linearAcceleration * cosf(_angle);
            _vy += delta * _linearAcceleration * sinf(_angle);
        }
        else if (inputs.isKeyDown(KEY_P2_MOVE_DOWN))
        {
            _vx -= delta * _linearAcceleration * cosf(_angle);
            _vy -= delta * _linearAcceleration * sinf(_angle);
        }

        if (inputs.isKeyDown(KEY_P2_MOVE_LEFT))
        {
            _angle -= delta * _turnSpeed;
        }
        else if (inputs.isKeyDown(KEY_P2_MOVE_RIGHT))
        {
            _angle += delta * _turnSpeed;
        }

        // Shooting
        if (inputs.isKeyDown(KEY_P2_FIRE_MISSILE))
        {
            for (int i = 0; i < 10; ++i)
                shootMissile();
        }

        if (inputs.isKeyDown(KEY_P2_FIRE_LASER))
            shootLaser();
    }
}

bool Player::isAlive() { return _alive; }
int Player::getId() { return 0; }

bool Player::collides() { return true; }

// Checks for collisions with Missiles
bool Player::doesCollide(int id)
{
    return id == 1 || id == 4;
}

void Player::collideEntity(Entity& entity)
{
    if (!_alive)
        return;

    if (_timeAlive >= _invincibleTime || _hasFired)
    {
        switch (entity.getId())
        {
        case 1:
            // If colliding with a Missile, die when it's from another Player
            if (dynamic_cast<Missile*>(&entity)->getPlayerNum() != _playerNum)
            {
                spawnExplosion();
                _alive = false;
                invoke(Event::SHIP_DESTROYED);
            }
            break;
        case 4:
            // If colliding with a Missile, die when it's from another Player
            if (dynamic_cast<Laser*>(&entity)->getPlayerNum() != _playerNum)
            {
                spawnExplosion();
                _alive = false;
                invoke(Event::SHIP_DESTROYED);

            }
            break;
        default:
            break;
        }
    }
}
void Player::invoke(Event event)
{
    // TODO : notify each observer
    for (auto observer : observers_)
    {
        observer->notify(event);
    }

}
void Player::addObserver(obs::IObserver* obs)
{
    auto itResult = std::find(observers_.begin(), observers_.end(), obs);

    if (itResult == observers_.end())
    {
        observers_.push_back(obs);
        cout << "observer added" << endl;
    }
}
void Player::remove(obs::IObserver* remove)
{
    /*auto it = observers_.begin();
	auto itEnd = observers_.end();*/
    //for (; it != itEnd; ++it)
    //{
    //    if (*it == remove)
    //    {
    //        observers_.erase(it); // expensive because it has to move everything o the left
    //        cout << "observer removed" << endl;
    //        break;
    //    }
    //}
    // I believe this line is a cleaner version to the for loop and if statement. simply use std remove
    // and reduce 5 - 7 lines of code to just one. To remove from beginning to end of the Vector.
    std::remove(observers_.begin(), observers_.end(), remove);
}

int Player::getPlayerNum() const { return _playerNum; }
