#pragma once

#include "Player.h"
#include "RessourcesManager.h"
#include "StonebrickBlock.h"
#include "StringHelpers.h"
#include "PlayerSurroundings.hpp"
#include "ABlock.h"
#include "Map.h"

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
private:
    const RessourcesManager     ressourcesManager;

    static const sf::Time	    TimePerFrame; // Todo remove
    static const float          GRAVITY; 

    sf::RenderWindow            window;
    Player	                    player;
    PlayerSurroundings          playerSurroundings;
    sf::Font	                font;
    sf::Text	                statisticsText;
    sf::Time	                statisticsUpdateTime;
    std::size_t	                statisticsNumFrames;
    bool                        isMovingUp;
    bool                        isMovingDown;
    bool                        isMovingRight;
    bool                        isMovingLeft;
    Map                         map;
    sf::Vector2u                sizeMario;

public:
    Game(const RessourcesManager&);
	~Game() {};
	void run();

private:
    void processEvents();
    void update(sf::Time);
    void render();

    void applyMovementConstraints(sf::Vector2f&, const sf::Time&);

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key, bool);
    //ABlock& getPlayerFirstCollision(int entityType);
};
