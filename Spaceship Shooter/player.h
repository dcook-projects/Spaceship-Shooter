#pragma once

#include <SDL.h>
#include <vector>
#include "playerprojectile.h"

struct App;

class Player
{
public:
	Player();
	~Player();

	void handleMoveEvent(SDL_Event& e);
	void move(App& app);
	void render(App& app);
	void initialize();
	void shoot();
	void setXPosition(int x);
	SDL_Rect getCollider() const;
	void clearShots() const;

	int getVelocityX() {
		return velX;
	}

private:
	//player ship attributes
	static constexpr int PLAYER_VEL = 7;
	static constexpr int PLAYER_WIDTH = 50;
	static constexpr int PLAYER_HEIGHT = 50;

	SDL_Rect collider;
	int posX, posY;
	int velX, velY;

	std::vector<PlayerProjectile *> playerShots;
};