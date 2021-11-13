/*
* David Cook
* 
* This is a simple shooting game, where you control your ship at the bottom of the screen. The objective is
* to shoot all the enemy ships, while you avoid being shot and rammed yourself.
*/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include "app.h"
#include "logic.h"
#include "stopwatch.h"
#include "particle.h"

bool init(App& app);
bool loadMedia(App& app);
void close(App& app);

void renderInfo(App& app);

bool init(App& app) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL failed to initialize\n");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	}

	app.window = SDL_CreateWindow("Spaceship Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (app.window == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	app.renderer = SDL_CreateRenderer(app.window, -1, SDL_RENDERER_ACCELERATED); //| SDL_RENDERER_PRESENTVSYNC);
	if (app.renderer == nullptr) {
		printf("%s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	//initialize audio
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

bool loadMedia(App& app) {

	//load game objects
	if (!app.playerTexture.loadFromFile(app, "assets/playership.png")) {
		printf("failed to load player texture\n");
		return false;
	}

	if (!app.easyEnemyTexture.loadFromFile(app, "assets/easyenemy.png")) {
		printf("failed to load easy enemy texture\n");
		return false;
	}

	if (!app.mediumEnemyTexture.loadFromFile(app, "assets/mediumenemy.png")) {
		printf("failed to load easy enemy texture\n");
		return false;
	}

	if (!app.hardEnemyTexture.loadFromFile(app, "assets/hardenemy.png")) {
		printf("failed to load easy enemy texture\n");
		return false;
	}

	if (!app.playerProjectileTexture.loadFromFile(app, "assets/playerprojectile.png")) {
		printf("failed to load player projectile texture\n");
		return false;
	}

	if (!app.enemyProjectileTexture.loadFromFile(app, "assets/enemyprojectile.png")) {
		printf("failed to load enemy projectile texture\n");
		return false;
	}

	//load the background stars
	if (!app.blueStarTexture.loadFromFile(app, "assets/bluestar.png")) {
		printf("failed to load blue star texture\n");
		return false;
	}

	if (!app.redStarTexture.loadFromFile(app, "assets/redstar.png")) {
		printf("failed to load red star texture\n");
		return false;
	}

	if (!app.greenStarTexture.loadFromFile(app, "assets/greenstar.png")) {
		printf("failed to load green star texture\n");
		return false;
	}

	//load the font and text textures
	app.font = TTF_OpenFont("assets/ClassicChunky.ttf", 28);
	if (app.font == nullptr) {
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if (!app.pauseTextTexture.loadFromRenderedText(app, "PAUSED", { 255, 255, 255 })) {
		printf("failed to load pause text\n");
		return false;
	}

	if (!app.livesTitleTextTexture.loadFromRenderedText(app, "LIVES", { 255, 0, 0 })) {
		printf("failed to load lives title text\n");
		return false;
	}

	if (!app.scoreTitleTextTexture.loadFromRenderedText(app, "SCORE", { 255, 0, 0 })) {
		printf("failed to load score title text\n");
		return false;
	}

	if (!app.levelTitleTextTexture.loadFromRenderedText(app, "LEVEL", { 255, 0, 0 })) {
		printf("failed to load level title text\n");
		return false;
	}

	if (!app.gameOverTexture.loadFromRenderedText(app, "GAME OVER: CLICK TO RESTART", { 255, 255, 255 })) {
		printf("failed to load gamne over text\n");
		return false;
	}

	//load the music
	app.music = Mix_LoadMUS("assets/Warp_Drive_1.mp3");
	if (app.music == nullptr) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

	//make the stars a little transparent
	app.blueStarTexture.setAlpha(155);
	app.redStarTexture.setAlpha(155);
	app.greenStarTexture.setAlpha(155);

	return true;
}

void close(App& app) {
	//Destroy textures
	app.playerProjectileTexture.free();
	app.enemyProjectileTexture.free();
	app.playerTexture.free();
	app.easyEnemyTexture.free();
	app.mediumEnemyTexture.free();
	app.hardEnemyTexture.free();

	app.blueStarTexture.free();
	app.greenStarTexture.free();
	app.redStarTexture.free();

	app.pauseTextTexture.free();
	app.livesTextTexture.free();
	app.levelTextTexture.free();
	app.scoreTextTexture.free();
	app.livesTitleTextTexture.free();
	app.levelTitleTextTexture.free();
	app.scoreTitleTextTexture.free();
	app.gameOverTexture.free();

	//destroy music
	Mix_FreeMusic(app.music);
	app.music = nullptr;

	//destroy Font
	TTF_CloseFont(app.font);
	app.font = nullptr;

	//destroy window	
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	app.window = nullptr;
	app.renderer = nullptr;

	//quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void renderInfo(App& app) {
	std::stringstream currentDisplay;

	//render titles
	app.scoreTitleTextTexture.render(app, SCREEN_WIDTH / 4 - app.scoreTitleTextTexture.getWidth() / 2, 0);
	app.levelTitleTextTexture.render(app, SCREEN_WIDTH * 2 / 4 - app.levelTitleTextTexture.getWidth() / 2, 0);
	app.livesTitleTextTexture.render(app, SCREEN_WIDTH * 3 / 4 - app.livesTitleTextTexture.getWidth() / 2, 0);

	//render score data
	currentDisplay.str("");
	currentDisplay << app.score;
	app.scoreTextTexture.loadFromRenderedText(app, currentDisplay.str(), { 255, 255, 255 });
	app.scoreTextTexture.render(app, (SCREEN_WIDTH - app.scoreTitleTextTexture.getWidth()) / 4 - 30, app.scoreTitleTextTexture.getHeight() + 1);

	//render level data
	currentDisplay.str("");
	currentDisplay << app.currentLevel;
	app.levelTextTexture.loadFromRenderedText(app, currentDisplay.str(), { 255, 255, 255 });
	app.levelTextTexture.render(app, SCREEN_WIDTH * 2 / 4, app.levelTitleTextTexture.getHeight() + 1);

	//render lives data
	currentDisplay.str("");
	currentDisplay << app.numLives;
	app.livesTextTexture.loadFromRenderedText(app, currentDisplay.str(), { 255, 255, 255 });
	app.livesTextTexture.render(app, SCREEN_WIDTH * 3 / 4, app.livesTitleTextTexture.getHeight() + 1);
}

int main(int argc, char* argv[]) {
	srand(time(nullptr));

	static constexpr int FRAME_RATE = 60;
	static constexpr int MS_PER_FRAME = 1000 / FRAME_RATE;
	static constexpr int TIME_BETWEEN_SHOTS = 500;
	static constexpr int TRANSITION_TIME = 4000;
	static constexpr int MAX_DIVING_ENEMIES = 2;
	static constexpr int DESTINATION_VARIANCE = 150;
	bool quit = false, firstLevelNotCreated = true;		//flags
	SDL_Event e;
	App app;
	ParticleEngine starBackground(app);		//creates the background stars
	Uint32 previousTime = 0, currentTime; //used to calculate time intervals for the player firing
	Uint32 startTime, frameTime;   //used to calculate frame rate
	Stopwatch transitionTimer;  //used to keep track of how long the game is betweeen levels
	Stopwatch lifeLostTimer;	//used to keep track of how much time passed once the player lost a life
	
	if (!init(app))
		return EXIT_FAILURE;

	if (!loadMedia(app)) {
		//getchar();
		return EXIT_FAILURE;
	}

	//play the music
	Mix_PlayMusic(app.music, -1);

	while (!quit) {
		startTime = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT)
				quit = true;
			//handle the pause button
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
				if (app.status == RUNNING) {
					app.status = PAUSED;
					Mix_PauseMusic();
				}
				else if(app.status == PAUSED) {
					app.status = RUNNING;
					Mix_ResumeMusic();
				}
			}
			//handle the player firing--player will fire if enough time has elapsed since the last shot
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {  
				if (app.status == RUNNING) {
					currentTime = SDL_GetTicks();
					if (currentTime > previousTime + TIME_BETWEEN_SHOTS) {
						app.player.shoot();
						previousTime = currentTime;
					}
				}
			}
			//restart the game if there is a game over--either from losing all lives or completing all levels
			else if (app.status == GAME_OVER && e.type == SDL_MOUSEBUTTONDOWN) {
				app.currentLevel = 1;
				app.score = 0;
				app.numLives = 5;
				app.numEnemiesMoving = 0;
				createLevels(app);
				app.status = TRANSITION;

				for (int row = 0; row < MAX_ENEMY_ROWS; ++row)
					for (int col = 0; col < MAX_ENEMY_COLUMNS; ++col) {
						app.enemies[row][col].resetDiveRects();
						app.enemies[row][col].setVelocity(0, 0);
					}
			}

			app.player.handleMoveEvent(e);
		}	//end event queue handling

		if (app.status == LIFE_RECENTLY_LOST) {
			if (lifeLostTimer.getTicks() == 0)
				lifeLostTimer.start();

			if (lifeLostTimer.getTicks() >= TRANSITION_TIME) {
				lifeLostTimer.stop();
				app.player.setXPosition(75);
				app.status = RUNNING;
			}
		}

		//creates the first level
		if (app.status == TRANSITION && firstLevelNotCreated == true) {
			createLevels(app);
			firstLevelNotCreated = false;
		}

		if (app.status == RUNNING || app.status == TRANSITION || app.status == LIFE_RECENTLY_LOST) {
			//move player
			app.player.move(app);
		}

		starBackground.moveStars();

		//choose a random enemy to go into a dive
		if (app.status == RUNNING) { //|| app.status == TRANSITION) {
			if (app.numEnemiesMoving < MAX_DIVING_ENEMIES) {
				int row = rand() % MAX_ENEMY_ROWS;
				int col = rand() % MAX_ENEMY_COLUMNS;
				int offset = (rand() % DESTINATION_VARIANCE) - (DESTINATION_VARIANCE / 2);
				SDL_Rect diveDestination = app.player.getCollider();

				//make sure the offset didn't take the dive destination off screen
				diveDestination.x += offset;
				if (diveDestination.x < 0)
					diveDestination.x = 0;

				if (diveDestination.x + diveDestination.w > SCREEN_WIDTH)
					diveDestination.x = SCREEN_WIDTH - diveDestination.w;

				//make sure the randomly chosen enemy is alive and not moving
				if (app.enemies[row][col].status == Enemy::ALIVE && app.enemies[row][col].getYVelocity() == 0) {
					switch (app.enemies[row][col].enemyType) {
					case Enemy::HARD:
						app.enemies[row][col].setVelocity(0, HARD_ENEMY_VEL);
						break;
					case Enemy::MEDIUM:
						app.enemies[row][col].setVelocity(0, MEDIUM_ENEMY_VEL);
						break;
					case Enemy::EASY:
						app.enemies[row][col].setVelocity(0, EASY_ENEMY_VEL);
						break;
					}

					app.enemies[row][col].setDiveLocations(app, app.enemies[row][col].getCollider(), diveDestination);
					++app.numEnemiesMoving;
				}
			}
		}

		//fire projectiles from enemies and move said projectiles
		if (app.status == RUNNING || app.status == LIFE_RECENTLY_LOST) {
			for (int row = 0; row < MAX_ENEMY_ROWS; ++row)
				for (int col = 0; col < MAX_ENEMY_COLUMNS; ++col) {
					app.enemies[row][col].move(app);
					if(app.status == RUNNING)
						app.enemies[row][col].shoot();
				}
		}

		//Clear screen and begin rendering
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderClear(app.renderer);

		//render the background stars and player ship
		starBackground.renderStars(app);
		app.player.render(app);

		for (int row = 0; row < MAX_ENEMY_ROWS; ++row)
			for (int col = 0; col < MAX_ENEMY_COLUMNS; ++col)
				app.enemies[row][col].render(app);

		if(app.status == PAUSED)
			app.pauseTextTexture.render(app, (SCREEN_WIDTH - app.pauseTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - app.pauseTextTexture.getHeight()) / 2);

		if (app.status == GAME_OVER)
			app.gameOverTexture.render(app, 5, (SCREEN_HEIGHT - app.gameOverTexture.getHeight()) / 2);

		renderInfo(app);

		//Update screen
		SDL_RenderPresent(app.renderer);

		frameTime = SDL_GetTicks() - startTime;
		if(frameTime < MS_PER_FRAME)
			SDL_Delay(MS_PER_FRAME - frameTime);

		//create the next level and wait a few seconds
		if (app.status == TRANSITION) {
			if(!transitionTimer.isStarted())
				transitionTimer.start();

			createLevels(app);

			if (transitionTimer.getTicks() >= TRANSITION_TIME) {
				transitionTimer.stop();
				app.status = RUNNING;
			}
		}
	}

	Mix_HaltMusic();
	close(app);
	return 0;
}