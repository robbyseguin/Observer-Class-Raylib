#pragma once

#include "raylib.h"
// Offsets can be used to place the hit box more accurately

class HitBox 
{
	float _x, _y;
	int _xOffset, _yOffset, _w, _h;
	float _angle;
	float _radius;
	Vector2 _tl, _tr, _bl, _br;

public:
	HitBox(float xOffset, float yOffset, int w, int h);
	void updatePos(float x, float y, float angle);
	void renderCorners() const; // DEBUG METHOD
	int getCenterX() const;
	int getCenterY() const;
	float getRadius() const;
	Vector2 getTl() const;
	Vector2 getTr() const;
	Vector2 getBl() const;
	Vector2 getBr() const;
};
