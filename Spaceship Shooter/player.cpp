#include "player.h"
#include "app.h"
#include "logic.h"
#include "stopwatch.h"

Player::Player() {
    velX = 0;
    initialize();
}

Player::~Player() {
    for (PlayerProjectile* p : playerShots)
        delete p;
}

//set the initial status of the Player
void Player::initialize() {
    posX = (App::SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    posY = App::SCREEN_HEIGHT - PLAYER_HEIGHT - 5;

    collider.x = posX;
    collider.y = posY;
    collider.w = PLAYER_WIDTH;
    collider.h = PLAYER_HEIGHT;
}

// This sets the Player's X velocity constant on arrow key down, and sets it to 0 on arrow key up
void Player::handleMoveEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            velX -= PLAYER_VEL;
            break;
        case SDLK_RIGHT:
            velX += PLAYER_VEL;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            velX += PLAYER_VEL;
            break;
        case SDLK_RIGHT:
            velX -= PLAYER_VEL;
            break;
        }
    }
}

//handle the player firing--player will fire if enough time has elapsed since the last shot
void Player::handleFireEvent(App& app, SDL_Event& e, Stopwatch& playerFireTimer) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
        if (app.status == RUNNING) {
            if (playerFireTimer.getTicks() > App::TIME_BETWEEN_SHOTS) {
                this->shoot();
                playerFireTimer.start();
            }
        }
    }
}

void Player::move(App& app) {
    if (app.status == RUNNING || app.status == TRANSITION) {
        //Move the Player and their collider left or right, but only if the game is running or in transition
        posX += velX;
        collider.x += velX;


        //If the Player went too far to the left or right
        if ((posX < 0) || (posX + PLAYER_WIDTH > App::SCREEN_WIDTH))
        {
            posX -= velX;
            collider.x -= velX;
        }
    }

    //move the projectiles that the player fired
    for (auto it = playerShots.begin(); it != playerShots.end(); ++it) {
        (*it)->move(app);
    }

    //check for enemy shots colliding with the player
    if (checkEnemyShotCollisionWithPlayer(app) || checkEnemyCollisionWithPlayer(app)) {
        lifeLost(app);

        if (app.status != GAME_OVER) {
            app.status = LIFE_RECENTLY_LOST;
            this->setXPosition(App::SCREEN_WIDTH + 500);
        }
    }
}

void Player::render(App& app) {

    app.playerTexture.render(app, collider);

    //go through the vector of player shots and either render the ones on screen, or delete the ones off screen
    for (auto it = playerShots.begin(); it != playerShots.end(); ) {
        if ((*it)->isDead()) {
            delete* it;
            it = playerShots.erase(it);
        }
        else {
            (*it)->render(app);
            ++it;
        }
    }
}

//moves all player shots off screen
void Player::clearShots() const {
    for (auto it = playerShots.begin(); it != playerShots.end(); ++it) 
        (*it)->killShot();
}

void Player::setXPosition(int x) {
    posX = x;
    collider.x = posX;
}

SDL_Rect Player::getCollider() const {
    return collider;
}

//adds a new shot to the list of player shots
void Player::shoot() {
    playerShots.push_back(new PlayerProjectile(posX, PLAYER_WIDTH, PLAYER_HEIGHT));
}