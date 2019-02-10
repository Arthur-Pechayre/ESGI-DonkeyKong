#include "pch.h"
#include "StringHelpers.h"
#include "Game.h"
#include "CrackedStoneBrickBlock.h"

const float Game::PlayerSpeed = 150;
const float Game::GRAVITY = 200;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(const RessourcesManager& manager):
    _ressourcesManager(manager),
    _window(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close),
    _player(manager),
    _font(),
    _statisticsText(),
    _statisticsUpdateTime(),
    _statisticsNumFrames(0),
    _isMovingUp(false),
    _isMovingDown(false),
    _isMovingRight(false),
    _isMovingLeft(false)
{
	_window.setFramerateLimit(160);

	// Draw blocks
	//auto _sizeBlock = _TextureBlock.getSize();

	for (int i = 0; i < BLOCK_COUNT_X; i++) {
		for (int j = 0; j < BLOCK_COUNT_Y; j++) {
            auto neoBlock = CrackedStoneBrickBlock(this->_ressourcesManager);
		
            neoBlock.setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));
            
            printf("I: %f, WTFX: %f, WTFY: %f\n", i, 100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

			//_Block[i][j].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (j + 1));

			//std::shared_ptr<Entity> se = std::make_shared<Entity>();
			//se->m_sprite = _Block[i][j];
			//se->m_type = EntityType::block;
			//se->m_size = _TextureBlock.getSize();
			//se->m_position = _Block[i][j].getPosition();
			//EntityManager::m_Entities.push_back(se);

            _blocks.push_back(neoBlock);
		}
	}

	// Draw Echelles

	/*_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

	for (int i = 0; i < ECHELLE_COUNT; i++)
	{
		_Echelle[i].setTexture(_TextureEchelle);
		_Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y );

		std::shared_ptr<Entity> se = std::make_shared<Entity>();
		se->m_sprite = _Echelle[i];
		se->m_type = EntityType::echelle;
		se->m_size = _TextureEchelle.getSize();
		se->m_position = _Echelle[i].getPosition();
		EntityManager::m_Entities.push_back(se);
	}*/

	// Draw Mario
	/*_sizeMario = mTexture.getSize();
	sf::Vector2f posMario;
	posMario.x = 100.f + 70.f;
	posMario.y = BLOCK_SPACE * 5 - _sizeMario.y;*/

	_player = Player(this->_ressourcesManager);
    _player._facing = 1;
	//EntityManager::m_Entities.push_back(player);

	// Draw Statistic Font 

	_font.loadFromFile("Media/Sansation.ttf");
	_statisticsText.setString("Welcome to Donkey Kong 1981");
	_statisticsText.setFont(_font);
	_statisticsText.setPosition(5.f, 5.f);
	_statisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
            _window.close();
			break;
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
    //auto isOnLadder = getPlayerFirstCollision(EntityType::echelle);

    if (_isMovingUp /*&& isOnLadder*/) {
        movement.y -= PlayerSpeed + Game::GRAVITY;
    }

    if (/*!_player.grounded(_blocks)*/1) {
        movement.y += /*isOnLadder ? 0 :*/ Game::GRAVITY;
        if (_isMovingDown) {
            movement.y += PlayerSpeed;
        }
    }
    if (_isMovingLeft) {
        movement.x -= PlayerSpeed;
    }	
    if (_isMovingRight) {
        movement.x += PlayerSpeed;
    }
    // Normalisation vecteurs
    if (movement.x > 0) {
        movement.x = movement.x > Player::MAX_X_SPEED ? Player::MAX_X_SPEED : movement.x;
    } else {
        movement.x = movement.x < -Player::MAX_X_SPEED ? -Player::MAX_X_SPEED : movement.x;
    }
    if (movement.y > 0) {
        movement.y = movement.y > Player::MAX_Y_SPEED ? Player::MAX_Y_SPEED : movement.y;
    } else {
        movement.y = movement.y < -Player::MAX_Y_SPEED ? -Player::MAX_Y_SPEED : movement.y;
    }
    
    int prevFacing = _player._facing;
    _player._facing = movement.x == 0 ? _player._facing : movement.x > 1 ? 1 : -1;
    _player._facingChanged = prevFacing != _player._facing;
	_player.move(movement * elapsedTime.asSeconds());
    _player.updateHitboxes();
}

void Game::render()
{
	_window.clear();

    for (int i = 0; i < _blocks.size(); ++i) {
        printf("BEFORE => ");
        printf("%d %f %f", i, _blocks[i].getPosition().x, _blocks[i].getPosition().y);
      
        _window.draw(_blocks[i]);
        printf("AFTER\n");
	}

    printf("Facing : %d | Changed : %d\n", _player._facing, _player._facingChanged);

    if (_player._facingChanged) {
        sf::Vector2f movement(0.f, 0.f);

        movement.x += _player._facing * -_player.getGlobalBounds().width;
        _player.move(movement);
        _player._facingChanged = false;
        _player.scale(-1, 1);

    }
    _window.draw(_player);

    _window.draw(_statisticsText);
    _window.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	_statisticsUpdateTime += elapsedTime;
	_statisticsNumFrames += 1;

	if (_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		_statisticsText.setString(
			"Frames / Second = " + toString(_statisticsNumFrames) + "\n" +
			"Time / Update = " + toString(_statisticsUpdateTime.asMilliseconds() / _statisticsNumFrames) + "ms"
        );

		_statisticsUpdateTime -= sf::seconds(1.0f);
		_statisticsNumFrames = 0;
	}
    
    if (_statisticsUpdateTime >= sf::seconds(0.050f))
	{
        
		// Handle collision weapon enemies
	}
}

/*ABlock& Game::getPlayerFirstCollision(int entityType = -1)
{
    auto playerShape = _player.getGlobalBounds();

    for (auto e : _blocks) {
        auto eShape = e.getGlobalBounds();

        if ((e.m_type == entityType || entityType == -1) && eShape.intersects(playerShape)) {
            return e;
        }
    }

    return nullptr;
}*/

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
        _isMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
        _isMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
        _isMovingRight = isPressed;

	if (key == sf::Keyboard::Space)
	{
	}
}
