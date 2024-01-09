#include "clock.h"

#include "raylib.h"

Clock::Clock() 
    : _lastTime{GetTime()}
    , _delta{}
{}

void Clock::reset() 
{
	_lastTime = GetTime();
}

void Clock::tick() 
{
    float current_time = GetTime(); // current-last is in seconds
    _delta = (current_time - _lastTime);
    _lastTime = current_time;
}

float Clock::getDelta() const { return _delta; }
