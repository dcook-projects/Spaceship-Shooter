#pragma once

#include <SDL.h>

class EnemyProjectile;
struct App;

class Enemy {
public:
	enum {
		EASY,
		MEDIUM,
		HARD
	} enemyType;

	enum ENEMY_STATUS {
		ALIVE,
		DEAD
	} status;

	Enemy();
	void shoot();
	void render(App& app);
	void move(App& app);
	void setParameters(int x, int y);
	void clearShot();
	void setDiveLocations(App& app, SDL_Rect startingLocation, SDL_Rect destination);
	void setVelocity(int xVel, int yVel);
	void resetDiveRects();
	int getXVelocity() const { return velX; }
	int getYVelocity() const { return velY; }
	SDL_Rect getCollider() const;
	SDL_Rect getShotCollider() const;

private:
	//constants for projectile speeds
	static constexpr int EASY_ENEMY_PROJ_VEL = 7;
	static constexpr int MEDIUM_ENEMY_PROJ_VEL = 9;
	static constexpr int HARD_ENEMY_PROJ_VEL = 10;

	SDL_Rect collider;
	EnemyProjectile* shot;

	//position and speed values
	int posX, posY;
	int velX, velY;

	//keep track of the coordinates for an enemy dive motion--the enemy will start at startLocation,
	//move to endLocation, then move back to startLocation
	SDL_Rect startLocation;
	SDL_Rect endLocation;
};