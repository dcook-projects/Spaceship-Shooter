#include "logic.h"
#include "app.h"

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

bool isBoardEmpty(App& app) {
	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) 
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) 
			if (app.enemies[row][column].status == Enemy::ALIVE)
				return false;	//if a single enemy has the alive status, return false
		
	return true;
}

void lifeLost(App& app) {
	--app.numLives;

	if (app.numLives == 0)
		gameOver(app);
}

void gameOver(App& app) {
	app.status = GAME_OVER;
}

//this moves all the enemy shots off screen, so they can be destrotyed later
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
	};

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

bool checkPlayerShotCollisionWithEnemy(App& app, SDL_Rect collider) {
	SDL_Rect enemyCollider;
	SDL_Rect playerShotCollider = collider;

	for (int row = 0; row < App::MAX_ENEMY_ROWS; ++row) {
		for (int column = 0; column < App::MAX_ENEMY_COLUMNS; ++column) {
			enemyCollider = app.enemies[row][column].getCollider();
			if (app.enemies[row][column].status == Enemy::ALIVE) {

				//perform the separating axis test to see if there is a collision
				if (enemyCollider.y + enemyCollider.h <= playerShotCollider.y)
					continue;

				if (enemyCollider.y >= playerShotCollider.y + playerShotCollider.h)
					continue;

				if (enemyCollider.x + enemyCollider.w <= playerShotCollider.x)
					continue;

				if (enemyCollider.x >= playerShotCollider.x + playerShotCollider.w)
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
				//perform separating axis test to determine if there is a collision
				if (playerCollider.y + playerCollider.h <= enemyShotCollider.y)
					continue;

				if (playerCollider.y >= enemyShotCollider.y + enemyShotCollider.h)
					continue;

				if (playerCollider.x + playerCollider.w <= enemyShotCollider.x)
					continue;

				if (playerCollider.x >= enemyShotCollider.x + enemyShotCollider.w)
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

			//perform separating axis test to determine if there is a collision
			if (playerCollider.y + playerCollider.h <= enemyCollider.y)
				continue;

			if (playerCollider.y >= enemyCollider.y + enemyCollider.h)
				continue;

			if (playerCollider.x + playerCollider.w <= enemyCollider.x)
				continue;

			if (playerCollider.x >= enemyCollider.x + enemyCollider.w)
				continue;

			return true;
		}
	}

	return false;
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