#pragma once

#include <vector>
#include "clock.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "inputs.h"

constexpr int NUM_PLAYERS = 2;

class Entity;
class CollisionManager;
class TitleManager;
class Background;

class World 
{
    using EntityList = std::vector<Entity*>;

    static const float revive_delay;

    int _screenW, _screenH;
	Clock _clock;
	CollisionManager* _collisionManager;
    TitleManager& _titleManager;
    Background& _background;
    EntityList _entities;
    float _playerReviveTimers[NUM_PLAYERS];

    void checkSpawnPlayers();
    void updateEntities();
    void removeDeadEntities();

public:
    World() = delete;
	World(int screen_w, int screen_h, TitleManager& titleManager, Background& background);
	void update(Inputs& inputs);
	float getDelta() const;
    const EntityList& getEntities() const;
	~World();
};
