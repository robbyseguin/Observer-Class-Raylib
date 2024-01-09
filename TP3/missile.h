#pragma once

#include "Entity.h"

// Missile that travels from where it was fired at a given
// angle. Dies upon colliding with a Player with a different player_num or
// after 3 seconds. Does not check for collisions. If the missile moves out of
// screen bounds will wrap to the other side.
// Missiles follow enemy players by turning to face them.
class Missile: public Entity 
{
    // References
    EntityList& _entities;

    // General Variables
    float _speed; // Speed in px/sec
    float _angle;
    float _timeAlive;
    int _playerNum;
    bool _alive;

    // Helper Functions
    void spawnExplosion();

public:

    Missile(float x, float y, float speed, float angle, int playerNum,
            int screenW, int screenH, EntityList & entities);
    void update(float delta) override;
    void render(Resources* resources, float delta) override;
    bool isAlive() override;
    int getId() override;
    bool collides() override;
    bool doesCollide(int id) override;
    void collideEntity(Entity& entity) override;
    int getPlayerNum();
};
