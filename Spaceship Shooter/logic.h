#pragma once

#include <SDL.h>

struct App;
class Stopwatch;

bool isBoardEmpty(App& app);
void lifeLost(App& app);
void gameOver(App& app);
void clearEnemyShots(App& app);
void createLevels(App& app);
void increaseScore(App& app, int row, int column);
bool checkPlayerShotCollisionWithEnemy(App& app, SDL_Rect collider);
bool checkEnemyShotCollisionWithPlayer(App& app);
bool checkEnemyCollisionWithPlayer(App& app);
void handlePauseEvent(App& app, SDL_Event& e, Stopwatch& fireTimer);
void handleGameRestart(App& app, SDL_Event& e);
void selectDiveEnemies(App& app);
void moveEnemies(App& app);