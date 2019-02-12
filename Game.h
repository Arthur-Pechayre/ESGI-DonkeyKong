#pragma once

#include "Player.h"
#include "RessourcesManager.h"
#include "ABlock.h"
#include "Map.h"

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
private:
    const RessourcesManager _ressourcesManager;

    static const float		PlayerSpeed; // Todo remove
    static const sf::Time	TimePerFrame; // Todo remove
    static const float      GRAVITY; 

    sf::RenderWindow    _window;
    Player	            _player;
    sf::Font	        _font;
    sf::Text	        _statisticsText;
    sf::Time	        _statisticsUpdateTime;
    std::size_t	        _statisticsNumFrames;
    bool                _isMovingUp;
    bool                _isMovingDown;
    bool                _isMovingRight;
    bool                _isMovingLeft;
    Map                 _map;
    sf::Vector2u        _sizeMario;

public:
    

	Game(const RessourcesManager&);
	~Game() {};
	void run();

private:
    void processEvents();
    void update(sf::Time elapsedTime);
    void render();

    bool isPlayerGrounded();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    //ABlock& getPlayerFirstCollision(int entityType);
};
