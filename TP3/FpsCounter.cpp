#include "FpsCounter.h"
using namespace GS;
// PRIVATE HELPER FUNCTIONS

float FpsCounter::getAverage() const
{
	float sum = 0;
	for(int i = 0; i < NUM_FRAMES_SAMPLED; i++) 
		sum += _frameTimes[i];
	
	return 1 / (sum / NUM_FRAMES_SAMPLED);
}

// PUBLIC FUNCTIONS

FpsCounter::FpsCounter() 
{
	_frameCounter = 0;
	_updateTimer = 0;
	_fps = 0;

	for (int i=0; i<NUM_FRAMES_SAMPLED; i++)
        _frameTimes[i] = 0;
}

void FpsCounter::count(float delta)
{
	_frameTimes[_frameCounter] = delta;
	_frameCounter = (_frameCounter + 1) % NUM_FRAMES_SAMPLED;
	_updateTimer += delta;
	if (_updateTimer > UPDATE_DELAY) 
    {
		_updateTimer = 0;
		_fps = getAverage();
	}
}

float FpsCounter::getFps() const { return _fps; }
