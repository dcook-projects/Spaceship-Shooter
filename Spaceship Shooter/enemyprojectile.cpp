#include <SDL.h>
#include "enemyprojectile.h"
#include "app.h"
#include "logic.h"

EnemyProjectile::EnemyProjectile(int x, int y, int velocity) {
	posX = x;
	posY = y;
	velY = velocity;
	collider.x = x;
	collider.y = y;
	collider.w = ENEMY_PROJ_WIDTH;
	collider.h = ENEMY_PROJ_HEIGHT;
}

bool EnemyProjectile::isDead() const {
	if (posY > App::SCREEN_HEIGHT)
		return true;
	else
		return false;
}

SDL_Rect EnemyProjectile::getCollider() const {
	return collider;
}

void EnemyProjectile::render(App& app) const {
	app.enemyProjectileTexture.render(app, collider);
}

void EnemyProjectile::move() {
	posY += velY;
	collider.y += velY;
}

void EnemyProjectile::killShot() {
	posY = App::SCREEN_HEIGHT + 10;
	collider.y = posY;
}