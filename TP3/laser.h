#pragma once

#include "Entity.h"

// Laser that travels in a straight line from where it was fired at a given
// angle. Dies upon colliding with a Player with a different player_num or
// after 3 seconds. Does not check for collisions. If the laser moves out of
// screen bounds will wrap to the other side.
class Laser final : public Entity
{
    // References
    EntityList& _entities;

    float _speed; // Speed in px/sec
    float _angle;
    float _timeAlive;
    int _playerNum;
    bool _alive;

public:
    Laser(float x, float y, float speed, float angle, int player_num,
          int screenW, int screenH, EntityList& entities);
    void update(float delta) override;
    void render(Resources* resources, float delta) override;
    bool isAlive() override;
    int getId() override;
    bool collides() override;
    bool doesCollide(int id) override;
    void collideEntity(Entity& entity) override;
    int getPlayerNum() const;
};
