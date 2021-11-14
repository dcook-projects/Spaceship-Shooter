#include "enemy.h"
#include "enemyprojectile.h"
#include "app.h"
#include <cmath>

Enemy::Enemy() {
	velX = 0;
	velY = 0;
	shot = nullptr;

	//initialize the dive coordinates to negative values--they will be changed to valid values if the enemy is currenyl in a dive
	resetDiveRects();
}

Enemy::~Enemy() {
	if (shot == nullptr)
		delete shot;
}

void Enemy::shoot() {
	int die;

	die = rand() % 2000;
	if (status == ALIVE && shot == nullptr) {
		if(enemyType == EASY && die == 0)
			shot = new EnemyProjectile(posX + App::ENEMY_WIDTH / 2, posY + App::ENEMY_HEIGHT + 2, EASY_ENEMY_PROJ_VEL);
		else if (enemyType == MEDIUM && die <= 1)
			shot = new EnemyProjectile(posX + App::ENEMY_WIDTH / 2, posY + App::ENEMY_HEIGHT + 2, MEDIUM_ENEMY_PROJ_VEL);
		else if (enemyType == HARD && die <= 3)
			shot = new EnemyProjectile(posX + App::ENEMY_WIDTH / 2, posY + App::ENEMY_HEIGHT + 2, HARD_ENEMY_PROJ_VEL);
	}
}

void Enemy::render(App& app) {
	//draw the enemy texture depending on its difficulty type
	if (status == ALIVE) {
		if (enemyType == EASY)
			app.easyEnemyTexture.render(app, collider);
		else if (enemyType == MEDIUM)
			app.mediumEnemyTexture.render(app, collider);
		else if (enemyType == HARD)
			app.hardEnemyTexture.render(app, collider);
	}

	//draw the enemy shot, if it exists
	if (shot != nullptr) {
		if (shot->isDead()) {
			delete shot;
			shot = nullptr;
		}
		else 
			shot->render(app);
	}
}

void Enemy::move(App& app) {
	int midpoint;

	posX += velX;
	collider.x += velX;
	posY += velY;
	collider.y += velY;

	/*
	 *	If the current enemy is moving, then find the y-coordinate of the midpoint between the enemy's start
	 * location and its end location. This is the point where the enemy will start moving in the x direction
	 * in order to reach its destination, if necessary.
	 */
	if (startLocation.y > 0) {
		midpoint = (startLocation.y + endLocation.y) / 2;

		if (posY >= midpoint && velY > 0) {		//if the enemy is below the midpoint and moving down
			if (startLocation.x < endLocation.x) {		//if the start location and the enemy's current position are to the left of the end location
				if (posX < endLocation.x) {
					switch (enemyType) {
					case EASY:
						velX = EASY_ENEMY_VEL;
						break;
					case MEDIUM:
						velX = MEDIUM_ENEMY_VEL;
						break;
					case HARD:
						velX = HARD_ENEMY_VEL;
						break;
					}
				}
				else
					velX = 0;
			}
			else if (startLocation.x > endLocation.x)  {		//if the start location and the enemy's position are to the right of the end location
				if (posX >= endLocation.x) {
					switch (enemyType) {
					case EASY:
						velX = -EASY_ENEMY_VEL;
						break;
					case MEDIUM:
						velX = -MEDIUM_ENEMY_VEL;
						break;
					case HARD:
						velX = -HARD_ENEMY_VEL;
						break;
					}
				}
				else
					velX = 0;
			}
		}
		else if (posY <= midpoint && velY < 0) {	//if the enemy is above the midpoint and moving up
			if ((startLocation.x < endLocation.x)) {
				if (posX > startLocation.x) {
					switch (enemyType) {
					case EASY:
						velX = -EASY_ENEMY_VEL;
						break;
					case MEDIUM:
						velX = -MEDIUM_ENEMY_VEL;
						break;
					case HARD:
						velX = -HARD_ENEMY_VEL;
						break;
					}
				}
				else
					velX = 0;
			}
			else if (startLocation.x > endLocation.x) {
				if (posX < startLocation.x) {
					switch (enemyType) {
					case EASY:
						velX = EASY_ENEMY_VEL;
						break;
					case MEDIUM:
						velX = MEDIUM_ENEMY_VEL;
						break;
					case HARD:
						velX = HARD_ENEMY_VEL;
						break;
					}
				}
				else
					velX = 0;
			}
		}
	}

	//enemy reaches the lowest part of the dive
	if (posY > endLocation.y && velY > 0) {
		velY = -velY;
		velX = 0;
	}

	//enemy reaches its original height
	if (velY < 0 && posY == startLocation.y) {
		velX = 0;
		velY = 0;

		//Manually set the enemy's position to its original location due to it possibly being off by a few pixels
		posX = startLocation.x;
		collider.x = posX;
		posY = startLocation.y;
		collider.y = posY;

		--app.numEnemiesMoving;
		resetDiveRects();
	}

	if (shot != nullptr) {
		shot->move();
	}
}

void Enemy::setParameters(int x, int y) {
	posX = x;
	posY = y;
	collider.x = x;
	collider.y = y;
	collider.w = App::ENEMY_WIDTH;
	collider.h = App::ENEMY_HEIGHT;
}

//sets the velocity of an enemy when beginning a dive
void Enemy::setVelocity() {
	switch (enemyType) {
	case EASY:
		velY = EASY_ENEMY_VEL;
		break;
	case MEDIUM:
		velY = MEDIUM_ENEMY_VEL;
		break;
	case HARD:
		velY = HARD_ENEMY_VEL;
		break;
	}
}

void Enemy::resetVelocity() {
	velX = 0;
	velY = 0;
}

//immediately send the shot off screen, so it can be destroyed later
void Enemy::clearShot() {
	if (shot != nullptr)
		shot->killShot();
}

void Enemy::setDiveLocations(App& app, SDL_Rect startLocation, SDL_Rect destination) {
	this->startLocation = startLocation;
	this->endLocation = destination;
}

SDL_Rect Enemy::getCollider() const {
	return collider;
}

//first checks if the enemy shot is null--if so, return a SDL_Rect with all values set to -1, otherwise return the shot's collider
SDL_Rect Enemy::getShotCollider() const {
	if (shot == nullptr) {
		SDL_Rect returnRect;
		returnRect.x = -1;
		returnRect.y = -1;
		returnRect.w = -1;
		returnRect.h = -1;
		return returnRect;
	}
	else
		return shot->getCollider();
}

void Enemy::resetDiveRects() {
	startLocation.x = -1;
	startLocation.y = -1;
	startLocation.w = -1;
	startLocation.h = -1;
	endLocation.x = -1;
	endLocation.y = -1;
	endLocation.w = -1;
	endLocation.h = -1;
}