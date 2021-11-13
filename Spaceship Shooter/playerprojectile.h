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
	//projectile attributes
	static constexpr int PLAYER_PROJECTILE_VEL = 20;
	static constexpr int PLAYER_PROJ_WIDTH = 10;
	static constexpr int PLAYER_PROJ_HEIGHT = 25;

	int posX, posY;
	int velY;
	SDL_Rect collider;
};