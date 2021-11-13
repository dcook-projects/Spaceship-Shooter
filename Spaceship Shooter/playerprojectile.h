#pragma once

#include <SDL.h>
//#include "player.h"

struct App;

class PlayerProjectile {
public:
	PlayerProjectile(int playerXPos);

	void move(App& app);
	void render(App& app);
	SDL_Rect getCollider() const;
	bool isDead();
	void killShot();
private:
	int posX, posY;
	int velY;
	SDL_Rect collider;
};