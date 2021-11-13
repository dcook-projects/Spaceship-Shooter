#pragma once

struct App;
class MyTexture;

class Particle {
public:
	Particle(App &app, int x, int y);
	void render(App& app);
	void move();
	bool isDead();
private:
	static constexpr int STAR_VELOCITY = 4;
	int posX, posY;
	MyTexture *texture;
};