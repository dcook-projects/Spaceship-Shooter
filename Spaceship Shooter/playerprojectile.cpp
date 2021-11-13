#include "playerprojectile.h"
#include "app.h"
#include "logic.h"

PlayerProjectile::PlayerProjectile(int playerXPos) {
	posX = playerXPos + (App::PLAYER_WIDTH / 2);
	posY = App::SCREEN_HEIGHT - App::PLAYER_HEIGHT - PLAYER_PROJ_HEIGHT - 2;
	velY = -PLAYER_PROJECTILE_VEL;
	collider.x = posX;
	collider.y = posY;
	collider.w = PLAYER_PROJ_WIDTH;
	collider.h = PLAYER_PROJ_HEIGHT;
}

void PlayerProjectile::move(App& app) {
	posY += velY;
	collider.y += velY;

	if (checkPlayerShotCollisionWithEnemy(app, getCollider())) {
		killShot();

		if (isBoardEmpty(app)) {
			++app.currentLevel;
			app.player.clearShots();

			if (app.currentLevel <= 5)
				app.status = TRANSITION;
			else {
				--app.currentLevel;
				gameOver(app);
			}
		}
	}
}

void PlayerProjectile::render(App& app) {
	app.playerProjectileTexture.render(app, collider);
}

SDL_Rect PlayerProjectile::getCollider() const {
	return collider;
}

//returns true of the projectile flies past the top of the screen
bool PlayerProjectile::isDead() {
	if (posY < 0)
		return true;
	else
		return false;
}

//moves the projectile out of bounds to mark it as dead--used when a shot hits an enemy
void PlayerProjectile::killShot() {
	posY = -100;
	collider.y = posY;
}