#pragma once

#include <SDL.h>

struct App;

bool isBoardEmpty(App& app);
void lifeLost(App& app);
void gameOver(App& app);
void clearEnemyShots(App& app);
void createLevels(App& app);
void increaseScore(App& app, int row, int column);
bool checkPlayerShotCollisionWithEnemy(App& app, SDL_Rect collider);
bool checkEnemyShotCollisionWithPlayer(App& app);
bool checkEnemyCollisionWithPlayer(App& app);