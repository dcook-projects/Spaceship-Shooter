#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "mytexture.h"
#include "player.h"
#include "enemy.h"
#include "particleengine.h"

constexpr int SCREEN_WIDTH = 775;
constexpr int SCREEN_HEIGHT = 900;

//player and enemy dimensions
constexpr int PLAYER_WIDTH = 50;
constexpr int PLAYER_HEIGHT = 50;
constexpr int ENEMY_WIDTH = 35;
constexpr int ENEMY_HEIGHT = 35;

//maximum space in which enemies can appear
constexpr int MAX_ENEMY_ROWS = 5;
constexpr int MAX_ENEMY_COLUMNS = 10;

//object velocities
constexpr int PLAYER_VEL = 7;
constexpr int PLAYER_PROJECTILE_VEL = 20;
constexpr int EASY_ENEMY_VEL = 4;
constexpr int MEDIUM_ENEMY_VEL = 5;
constexpr int HARD_ENEMY_VEL = 6;

//projectile sizes
constexpr int PLAYER_PROJ_WIDTH = 10;
constexpr int PLAYER_PROJ_HEIGHT = 25;
constexpr int ENEMY_PROJ_WIDTH = 10;
constexpr int ENEMY_PROJ_HEIGHT = 25;


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