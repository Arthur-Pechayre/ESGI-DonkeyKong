#pragma once

#include "RessourcesManager.h"
#include "PlayerManager.h"
#include "EntityManager.h"
#include "StringHelpers.h"
#include "Map.h"

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
private:
    const RessourcesManager     ressourcesManager;

    sf::RenderWindow            window;
    PlayerManager               playerManager;
    Map                         map;

    static const sf::Time	    TimePerFrame; // Todo move in const.h

    sf::Font	                font; // Todo move in ressource manager
    sf::Text	                statisticsText; // Todo make ui 
    sf::Time	                statisticsUpdateTime;
    std::size_t	                statisticsNumFrames;
    bool                        isMovingUp; //To do move
    bool                        isMovingDown;
    bool                        isMovingRight;
    bool                        isMovingLeft;
    bool                        isJumping;

public:
    static const float          GRAVITY; // Todo move in const.h
    static const float          FRICTION; // Todo move in const.h

    Game(const RessourcesManager&);
	~Game() {};
	void run();

private:
    void processEvents();
    void update(const sf::Time&);
    void updatePlayer(const sf::Time&);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key, bool);
};
