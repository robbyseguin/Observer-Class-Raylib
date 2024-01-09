#pragma once

#include <vector>

#include "HitBox.h"
#include "resources.h"

class World;

class Entity
{
protected:
    using uchar = unsigned char;
    using EntityList = std::vector<Entity*>;

	float _x, _y;
	int _w, _h;
	int _screenW, _screenH;
	HitBox* _hitBox;

	float getCenterX() const;
	float getCenterY() const;
	void checkBounds();

public:
	Entity(float x, float y, int w, int h, int screenW, int screenH);
	HitBox& getHitBox() const;
	float getX() const;
	float getY() const;
	virtual ~Entity() = 0;
	virtual void update(float delta) = 0;
	virtual void render(Resources* resources, float delta) = 0;
	virtual bool isAlive() = 0;
	virtual int getId() = 0;
	virtual bool collides() = 0;
	virtual bool doesCollide(int id) = 0;
	virtual void collideEntity(Entity& entity) = 0;
};
