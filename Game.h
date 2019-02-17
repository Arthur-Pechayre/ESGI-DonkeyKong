#pragma once

#include "RessourcesManager.h"
#include "PlayerManager.h"
#include "EntityManager.h"
#include "StringHelpers.h"
#include "Score.h"
#include "Map.h"

class Game
{
private:
    static const sf::Time	    TimePerFrame;
    const RessourcesManager     ressourcesManager;

    sf::RenderWindow            window;
    PlayerManager               playerManager;
    EntityManager               entityManager;
    Map                         map;
    Score                       score;

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
    static const float          GRAVITY;
    static const float          FRICTION;

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
