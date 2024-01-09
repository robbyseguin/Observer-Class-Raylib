#pragma once

#include "graphics.h"

class Overlay 
{
	int _width, _height;
	Resources& _resources;

public:
	Overlay(int width, int height, Resources& resources);
	void renderFps(int fps);
};
