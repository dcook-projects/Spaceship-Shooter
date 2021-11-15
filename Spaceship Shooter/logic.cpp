#include "logic.h"
#include "app.h"
#include "stopwatch.h"
#include <SDL.h>

/*
 *	This goes through the enemy field in app and initializes them based on the passed in char[][]. The enemies
 *	are centered on the screen.
 */
void setEnemyPlacement(App& app, char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS]) {
	static constexpr int ENEMY_GAP = 10;
	static constexpr int ENEMY_FIELD_WIDTH = App::MAX_ENEMY_COLUMNS * App::ENEMY_WIDTH + (App::MAX_ENEMY_COLUMNS - 1) * ENEMY_GAP;
	static constexpr int TOP_GAP = 100;

	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int col = 0; col < App::MAX_ENEMY_COLUMNS; ++col) {
			if (enemyMap[row][col] == 'h') {
				app.enemies[row][col].setParameters((App::SCREEN_WIDTH - ENEMY_FIELD_WIDTH) / 2 + col * App::ENEMY_WIDTH + ENEMY_GAP * col, TOP_GAP + row * App::ENEMY_HEIGHT + ENEMY_GAP * row);
				app.enemies[row][col].enemyType = Enemy::HARD;
				app.enemies[row][col].status = Enemy::ALIVE;
			}
			else if (enemyMap[row][col] == 'm') {
				app.enemies[row][col].setParameters((App::SCREEN_WIDTH - ENEMY_FIELD_WIDTH) / 2 + col * App::ENEMY_WIDTH + ENEMY_GAP * col, TOP_GAP + row * App::ENEMY_HEIGHT + ENEMY_GAP * row);
				app.enemies[row][col].enemyType = Enemy::MEDIUM;
				app.enemies[row][col].status = Enemy::ALIVE;
			}
			else if (enemyMap[row][col] == 'e') {
				app.enemies[row][col].setParameters((App::SCREEN_WIDTH - ENEMY_FIELD_WIDTH) / 2 + col * App::ENEMY_WIDTH + ENEMY_GAP * col, TOP_GAP + row * App::ENEMY_HEIGHT + ENEMY_GAP * row);
				app.enemies[row][col].enemyType = Enemy::EASY;
				app.enemies[row][col].status = Enemy::ALIVE;
			}
			else {
				app.enemies[row][col].setParameters((App::SCREEN_WIDTH - ENEMY_FIELD_WIDTH) / 2 + col * App::ENEMY_WIDTH + ENEMY_GAP * col, TOP_GAP + row * App::ENEMY_HEIGHT + ENEMY_GAP * row);
				app.enemies[row][col].enemyType = Enemy::EASY;
				app.enemies[row][col].status = Enemy::DEAD;
			}
		}
	}
}

//checks if all enemies are dead, so the next level can be loaded or game ended
bool isBoardEmpty(App& app) {
	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) 
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) 
			if (app.enemies[row][column].status == Enemy::ALIVE)
				return false;	//if a single enemy has the alive status, return false
		
	return true;
}

//code that executes when the player collides with an enemy or an enemy shot
void lifeLost(App &app) {
	--app.numLives;

	if (app.numLives == 0)
		gameOver(app);
}

//code that executes when all lives are lost or the player beats all the levels
void gameOver(App& app) {
	app.status = GAME_OVER;
}

//this moves all the enemy shots off screen, so they can be destroyed later
void clearEnemyShots(App& app) {
	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) {
			app.enemies[row][column].clearShot();
		}
	}
}

void createFirstLevel(App& app) {
	char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS] = {		{'\0', '\0', '\0', 'h', 'h', 'h', 'h', '\0', '\0', '\0'},
																		{'\0', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', '\0'},
																		{'\0', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', '\0'},
																		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
																		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}
	};																	// \0 = no enemy in that spot, h = hard enemy, m = medium enemy, e = easy enemy

	setEnemyPlacement(app, enemyMap);
}

void createSecondLevel(App& app) {
	char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS] = {		{'\0', '\0', 'h', 'h', 'h', 'h', 'h', 'h', '\0', '\0'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
																		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
																		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}
	};

	setEnemyPlacement(app, enemyMap);
}

void createThirdLevel(App& app) {
	char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS] = {		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
																		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'}
	};

	setEnemyPlacement(app, enemyMap);
}

void createFourthLevel(App& app) {
	char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS] = {		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'},
																		{'m', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm', 'm'}
	};

	setEnemyPlacement(app, enemyMap);
}

void createFifthLevel(App& app) {
	char enemyMap[App::MAX_ENEMY_ROWS][App::MAX_ENEMY_COLUMNS] = {		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'},
																		{'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h', 'h'}
	};

	setEnemyPlacement(app, enemyMap);
}

void createLevels(App& app) {
	switch (app.currentLevel) {
	case 1:
		createFirstLevel(app);
		break;
	case 2:
		createSecondLevel(app);
		break;
	case 3:
		createThirdLevel(app);
		break;
	case 4:
		createFourthLevel(app);
		break;
	case 5:
		createFifthLevel(app);
		break;
	}
}

//perform the separating axis test to see if there is a collision
bool separatingAxisText(SDL_Rect colliderOne, SDL_Rect colliderTwo) {
	if (colliderOne.y + colliderOne.h <= colliderTwo.y)
		return false;;

	if (colliderOne.y >= colliderTwo.y + colliderTwo.h)
		return false;

	if (colliderOne.x + colliderOne.w <= colliderTwo.x)
		return false;

	if (colliderOne.x >= colliderTwo.x + colliderTwo.w)
		return false;

	return true;
}

bool checkPlayerShotCollisionWithEnemy(App& app, SDL_Rect collider) {
	SDL_Rect enemyCollider;
	SDL_Rect playerShotCollider = collider;

	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) {
			enemyCollider = app.enemies[row][column].getCollider();
			if (app.enemies[row][column].status == Enemy::ALIVE) {

				if (separatingAxisText(playerShotCollider, enemyCollider) == false)
					continue;

				app.enemies[row][column].status = Enemy::DEAD;
				increaseScore(app, row, column);

				//reduce the total number of enemies moving if one was shot in the middle of a dive
				if (app.enemies[row][column].getYVelocity() != 0 || app.enemies[row][column].getXVelocity() != 0) {
					app.enemies[row][column].resetVelocity();
					--app.numEnemiesMoving;
				}

				return true;
			}
		}
	}

	return false;
}

bool checkEnemyShotCollisionWithPlayer(App& app) {  
	SDL_Rect playerCollider = app.player.getCollider();
	SDL_Rect enemyShotCollider;

	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) {
			enemyShotCollider = app.enemies[row][column].getShotCollider();

			//check that a collider with non negative values was returned
			if (enemyShotCollider.x > 0) {
				
				if (separatingAxisText(playerCollider, enemyShotCollider) == false)
					continue;

				return true;
			}
		}
	}

	return false;
}

bool checkEnemyCollisionWithPlayer(App& app) {
	SDL_Rect enemyCollider;
	SDL_Rect playerCollider = app.player.getCollider();

	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) {
			enemyCollider = app.enemies[row][column].getCollider();

			if (separatingAxisText(enemyCollider, playerCollider) == false)
				continue;

			return true;
		}
	}

	return false;
}

//handle the pause button--this also pauses and unpauses the player fire timer
void handlePauseEvent(App& app, SDL_Event& e, Stopwatch& playerFireTimer) {
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
		if (app.status == RUNNING) {
			app.status = PAUSED;
			playerFireTimer.pause();
			Mix_PauseMusic();
		}
		else if (app.status == PAUSED) {
			app.status = RUNNING;
			playerFireTimer.unpause();
			Mix_ResumeMusic();
		}
	}
}

//restart the game if there is a game over--either from losing all lives or completing all levels
void handleGameRestart(App& app, SDL_Event& e) {
	if (app.status == GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN) {
		app.currentLevel = 1;
		app.score = 0;
		app.numLives = 5;
		app.numEnemiesMoving = 0;
		createLevels(app);
		app.status = TRANSITION;
		app.player.clearShots();
		clearEnemyShots(app);

		for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row)
			for (int col = 0; col < App::MAX_ENEMY_COLUMNS; ++col) {
				app.enemies[row][col].resetDiveRects();
				app.enemies[row][col].resetVelocity();
			}
	}
}

//choose random enemies to go into a dive
void selectDiveEnemies(App& app) {
	if (app.status == RUNNING) {
		if (app.numEnemiesMoving < App::MAX_DIVING_ENEMIES) {
			int row = rand() % App::MAX_ENEMY_ROWS;
			int col = rand() % App::MAX_ENEMY_COLUMNS;
			int offset = (rand() % App::DESTINATION_VARIANCE) - (App::DESTINATION_VARIANCE / 2);
			SDL_Rect diveDestination = app.player.getCollider();

			//make sure the offset didn't take the dive destination off screen
			diveDestination.x += offset;
			if (diveDestination.x < 0)
				diveDestination.x = 0;

			if (diveDestination.x + diveDestination.w > App::SCREEN_WIDTH)
				diveDestination.x = App::SCREEN_WIDTH - diveDestination.w;

			//make sure the randomly chosen enemy is alive and not moving
			if (app.enemies[row][col].status == Enemy::ALIVE && app.enemies[row][col].getYVelocity() == 0) {
				app.enemies[row][col].setVelocity();
				app.enemies[row][col].setDiveLocations(app.enemies[row][col].getCollider(), diveDestination);
				++app.numEnemiesMoving;
			}
		}
	}
}

//move enemies that are diving and enemy shots
void moveEnemies(App& app) {
	if (app.status == RUNNING || app.status == LIFE_RECENTLY_LOST) {
		for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row)
			for (int col = 0; col < App::MAX_ENEMY_COLUMNS; ++col) {
				app.enemies[row][col].move(&(app.numEnemiesMoving));
				if (app.status == RUNNING)
					app.enemies[row][col].shoot();	//the function that rolls a die to see if the enemy will shoot this frame
			}
	}
}

void increaseScore(App& app, int row, int column) {
	switch (app.enemies[row][column].enemyType) {
	case Enemy::EASY:
		app.score += 100;
		break;
	case Enemy::MEDIUM:
		app.score += 200;
		break;
	case Enemy::HARD:
		app.score += 300;
		break;
	}
}