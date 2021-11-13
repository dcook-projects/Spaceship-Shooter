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
	//projectile attributes
	static constexpr int ENEMY_PROJ_WIDTH = 10;
	static constexpr int ENEMY_PROJ_HEIGHT = 25;

	int posX, posY;
	int velY;
	SDL_Rect collider;
};