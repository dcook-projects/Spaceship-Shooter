#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "mytexture.h"
#include "player.h"
#include "enemy.h"
#include "particleengine.h"

//tracks the status that the game is currently in
enum Game_Status {
	PAUSED,
	RUNNING,
	LIFE_RECENTLY_LOST,
	TRANSITION,
	GAME_OVER
};

struct App {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;
	Mix_Music* music = nullptr;

	/* GAME CONSTANTS*/
	//window dimensions
	static constexpr int SCREEN_WIDTH = 775;
	static constexpr int SCREEN_HEIGHT = 900;

	//enemy ship dimensions
	static constexpr int ENEMY_WIDTH = 35;
	static constexpr int ENEMY_HEIGHT = 35;

	//maximum space in which enemies can appear
	static constexpr int MAX_ENEMY_ROWS = 5;
	static constexpr int MAX_ENEMY_COLUMNS = 10;

	//other game constants
	static constexpr int FRAME_RATE = 60;
	static constexpr int MS_PER_FRAME = 1000 / FRAME_RATE;
	static constexpr int TIME_BETWEEN_SHOTS = 500;
	static constexpr int TRANSITION_TIME = 4000;
	static constexpr int MAX_DIVING_ENEMIES = 2;
	static constexpr int DESTINATION_VARIANCE = 150;

	//game object textures
	MyTexture playerTexture;
	MyTexture easyEnemyTexture;
	MyTexture mediumEnemyTexture;
	MyTexture hardEnemyTexture;
	MyTexture playerProjectileTexture;
	MyTexture enemyProjectileTexture;
	MyTexture greenStarTexture;
	MyTexture redStarTexture;
	MyTexture blueStarTexture;

	//text textures
	MyTexture pauseTextTexture;
	MyTexture livesTitleTextTexture;
	MyTexture livesTextTexture;
	MyTexture scoreTitleTextTexture;
	MyTexture scoreTextTexture;
	MyTexture levelTitleTextTexture;
	MyTexture levelTextTexture;
	MyTexture gameOverTexture;

	//tracks the current game state
	Game_Status status = TRANSITION;

	//represents the player ship
	Player player;

	//represents the enemies
	Enemy enemies[MAX_ENEMY_ROWS][MAX_ENEMY_COLUMNS];

	unsigned int score = 0;
	int numLives = 5;
	int currentLevel = 1;
	int numEnemiesMoving = 0;
};