#pragma once

#include "Entity.h"

// Simple particle-like entity which is spawned which a Player explodes.
class ShipPart final : public Entity 
{
    // Speed in px/sec
    float _timeAlive;
    float _lifetime;
    float _vx, _vy;
    float _angle;
    float _rotSpeed;
    int _playerNum;
    int _type;

public:
    ShipPart(float x, float y, float vx, float vy, float rotSpeed,
             float lifetime, int playerNum, int type, int screenW,
             int screenH);
    void update(float delta) override;
    void render(Resources* resources, float delta) override;
    bool isAlive() override;
    int getId() override;
    bool collides() override;
    bool doesCollide(int id) override;
    void collideEntity(Entity& entity) override;
};
