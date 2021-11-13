#include "particleengine.h"
#include "particle.h"
#include "app.h"

ParticleEngine::ParticleEngine(App& app) {
	for (int row = 25; row < SCREEN_HEIGHT - 25; row += 50) {
		for (int starCount = 0; starCount < 2; ++starCount) {
			int yPos = (rand() % 51) - 25 + row;
			int xPos = rand() % SCREEN_WIDTH;
			stars.push_back(new Particle(app, xPos, yPos));
		}
	}
}

ParticleEngine::~ParticleEngine() {
	for (auto it = stars.begin(); it != stars.end(); ) {
		delete* it;
		it = stars.erase(it);
	}
}

void ParticleEngine::moveStars() {
	for (Particle* p : stars)
		p->move();
}

void ParticleEngine::renderStars(App& app) {
	for (auto it = stars.begin(); it != stars.end(); ) {
		if ((*it)->isDead()) {
			//if a star is dead, then create a new one right before deleting the old one
			int xPos = rand() % SCREEN_WIDTH;
			int yPos = -15;
			stars.push_back(new Particle(app, xPos, yPos));

			delete* it;
			it = stars.erase(it);
		}
		else {
			(*it)->render(app);
			++it;
		}
	}
}