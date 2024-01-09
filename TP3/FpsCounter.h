#pragma once

namespace GS
{
    class FpsCounter
    {
        enum { NUM_FRAMES_SAMPLED = 10 };

        // Interval in seconds before updating FPS calculation
        inline static constexpr float UPDATE_DELAY = 0.25f;

        float _frameTimes[NUM_FRAMES_SAMPLED];
        int _frameCounter;
        float _updateTimer;
        float _fps;

        float getAverage() const;

    public:
        FpsCounter();

        void count(float delta);
        float getFps() const;
    };
}
