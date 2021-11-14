#include "stopwatch.h"

Stopwatch::Stopwatch() {
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Stopwatch::start() {
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
	pausedTicks = 0;
}

void Stopwatch::stop() {
	started = false;
	paused = false;
	startTicks = 0;
	pausedTicks = 0;
}

void Stopwatch::pause() {
	if (started && !paused) {
		paused = true;

		pausedTicks = SDL_GetTicks() - startTicks;
		startTicks = 0;
	}
}

void Stopwatch::unpause() {
	if (started && paused) {
		paused = false;

		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

//returns the actual time on the stopwatch (in milliseconds)
Uint32 Stopwatch::getTicks() const {
	Uint32 time = 0;

	if (started) {
		if (paused)
			time = pausedTicks;
		else
			time = SDL_GetTicks() - startTicks;
	}

	return time;
}