#pragma once

#include "RessourcesManager.h"
#include "PlayerManager.h"
#include "EntityManager.h"
#include "StringHelpers.h"
#include "Score.h"
#include "Map.h"

class Game
{
public:
    enum Status{
        End,
        Restart,
        Next
    };

private:
    static const sf::Time	    TimePerFrame;
    const RessourcesManager     ressourcesManager;

    sf::RenderWindow&           window;
    PlayerManager               playerManager;
    EntityManager               entityManager;
    Map                         map;
    Score                       score;

    sf::Text	                statisticsText;
    sf::Time	                statisticsUpdateTime;
    std::size_t	                statisticsNumFrames;
    bool                        isMovingUp;
    bool                        isMovingDown;
    bool                        isMovingRight;
    bool                        isMovingLeft;
    bool                        isJumping;

public:
    Game(sf::RenderWindow&, const RessourcesManager&, const std::string&);
	~Game() {};
    Game::Status run();

private:
    void processEvents();
    void update(const sf::Time&);
    void updatePlayerPosition(const sf::Time&);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key, bool);
};
