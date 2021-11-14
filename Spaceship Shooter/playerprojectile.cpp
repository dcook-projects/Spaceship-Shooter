#include "playerprojectile.h"
#include "app.h"
#include "logic.h"

PlayerProjectile::PlayerProjectile(int playerXPos, int playerWidth, int playerHeight) {
	posX = playerXPos + (playerWidth / 2);
	posY = App::SCREEN_HEIGHT - playerHeight - PLAYER_PROJ_HEIGHT - 2;
	velY = -PLAYER_PROJECTILE_VEL;
	collider.x = posX;
	collider.y = posY;
	collider.w = PLAYER_PROJ_WIDTH;
	collider.h = PLAYER_PROJ_HEIGHT;
}

void PlayerProjectile::move(App& app) {
	posY += velY;
	collider.y += velY;

	//check if the player hit an enemy every time a player shot moves
	if (checkPlayerShotCollisionWithEnemy(app, getCollider())) {
		killShot();

		//check if all enemy ships are destroyed
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

void PlayerProjectile::render(App& app) const {
	app.playerProjectileTexture.render(app, collider);
}

SDL_Rect PlayerProjectile::getCollider() const {
	return collider;
}

//returns true of the projectile flies past the top of the screen
bool PlayerProjectile::isDead() const {
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