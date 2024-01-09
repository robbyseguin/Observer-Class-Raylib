#pragma once

#include "entity.h"

// Particles are small dots that move at a set (vx, vy).
// There are 3 types (different colors). They die after (lifetime)
// seconds, and fade (with decreasing opacity) as they age.
class Particle: public Entity 
{
    float _timeAlive;
    float _lifetime;
    float _vx, _vy; // Speed in px/s
    int _type;

public:

    Particle(float x, float y, float vx, float vy, float lifetime, int type,
             int screenW, int screenH);
    void update(float delta) override;
    void render(Resources* resources, float delta) override;
    bool isAlive() override;
    int getId() override;
    bool collides() override;
    bool doesCollide(int id) override;
    void collideEntity(Entity& entity) override;
};
