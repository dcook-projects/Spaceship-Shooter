#pragma once

#include <SDL.h>
#include "app.h"

class EnemyProjectile {
public:
	EnemyProjectile(int x, int y, int velocity);
	void move();
	void render(App& app);
	void killShot();
	bool isDead();
	SDL_Rect getCollider() const;
private:
	int posX, posY;
	int velY;
	SDL_Rect collider;
};