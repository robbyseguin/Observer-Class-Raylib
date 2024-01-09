#pragma once

// Keeps track of 'delta' times between frames
class Clock 
{
    double _lastTime;
	float _delta;

public:
	// The first delta begins as soon as the clock is created
	Clock();
	// Sets last_time to SDL_GetTicks()
	void reset();
	// Returns the delta time in seconds between the last two calls to tick()
	float getDelta() const;
	// Recalculates then resets the delta
	void tick();
	
};