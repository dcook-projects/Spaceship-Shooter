#pragma once

#include <SDL.h>

class Stopwatch
{
public:
    Stopwatch();
    void start();
    void stop();
    void pause();
    void unpause();
    Uint32 getTicks() const;

    bool isStarted() { return started; }
    bool isPaused() { return paused; }

private:
    //The clock time when the timer started
    Uint32 startTicks;

    //The ticks stored when the timer was paused
    Uint32 pausedTicks;

    bool started;
    bool paused;
};