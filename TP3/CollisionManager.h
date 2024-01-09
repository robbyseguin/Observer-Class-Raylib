#pragma once

#include <vector>
#include "Entity.h"

class Entity;

class CollisionManager
{
    using EntityList = std::vector<Entity*>;
    EntityList& _entities;

public:
	CollisionManager(EntityList& entities);
	void checkCollisions() const;
};