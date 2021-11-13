#pragma once

#include <vector>

struct App;
class Particle;

class ParticleEngine {
public:
	ParticleEngine(App &app);
	~ParticleEngine();

	void moveStars();
	void renderStars(App& app);
private:
	std::vector<Particle *> stars;
};