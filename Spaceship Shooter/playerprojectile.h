#pragma once

#include <SDL.h>
//#include "player.h"

struct App;

class PlayerProjectile {
public:
	PlayerProjectile(int playerXPos, int playerWidth, int playerHeight);

	void move(App& app);
	void render(App& app) const;
	SDL_Rect getCollider() const;
	bool isDead() const;
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