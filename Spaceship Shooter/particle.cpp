#include "particle.h"
#include "app.h"

//initialize variables and determine which star this will be using RNG
Particle::Particle(App& app, int x, int y) {
	posX = x;
	posY = y;
	texture = nullptr;

	switch (rand() % 3) {
	case 0:
		texture = &app.blueStarTexture;
		break;
	case 1:
		texture = &app.redStarTexture;
		break;
	case 2:
		texture = &app.greenStarTexture;
		break;
	}
}

//a star is dead if it goes below the screen
bool Particle::isDead() {
	if (posY > App::SCREEN_HEIGHT)
		return true;
	else
		return false;
}

void Particle::move() {
	posY += STAR_VELOCITY;
}

void Particle::render(App& app) {
	texture->render(app, posX, posY);
}