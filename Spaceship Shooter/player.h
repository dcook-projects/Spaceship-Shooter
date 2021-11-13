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
	void handleFireEvent(SDL_Event& e);
	void move(App& app);
	void render(App& app);
	void initialize();
	void shoot();
	int getXPosition() const;
	void setXPosition(int x);
	SDL_Rect getCollider() const;
	void clearShots();

	int getVelocityX() {
		return velX;
	}

private:
	SDL_Rect collider;
	int posX, posY;
	int velX, velY;

	std::vector<PlayerProjectile *> playerShots;
};