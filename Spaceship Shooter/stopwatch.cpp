#include "stopwatch.h"

Stopwatch::Stopwatch() {
	started = false;
	startTicks = 0;
}

void Stopwatch::start() {
	started = true;
	startTicks = SDL_GetTicks();
}

void Stopwatch::stop() {
	started = false;
	startTicks = 0;
}

Uint32 Stopwatch::getTicks() {
	Uint32 time = 0;

	if (started) 
		time = SDL_GetTicks() - startTicks;

	return time;
}