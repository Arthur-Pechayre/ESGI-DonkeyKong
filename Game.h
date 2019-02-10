#pragma once

#include "Player.h"
#include "RessourcesManager.h"
#include "ABlock.h"

#define ECHELLE_COUNT 4
#define BLOCK_COUNT_X 8
#define BLOCK_COUNT_Y 5
#define BLOCK_SPACE 110.f

class Game
{
    typedef std::vector<ABlock> BlockList;

public:
	Game(const RessourcesManager&);
	~Game() {};
	void run();

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;
    static const float      GRAVITY;

    const RessourcesManager _ressourcesManager;

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
    BlockList           _blocks;
	sf::Vector2u        _sizeMario;

private:
    void processEvents();
    void update(sf::Time elapsedTime);
    void render();

    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    //ABlock& getPlayerFirstCollision(int entityType);
};
