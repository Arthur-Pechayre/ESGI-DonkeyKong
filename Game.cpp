#include "pch.h"
#include "Game.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(const RessourcesManager& manager, const std::string& mapPath):
    window(sf::VideoMode(1920, 1080), "Not Donkey Kong 1981", sf::Style::Close + sf::Style::Resize),
    ressourcesManager(manager),
    map(manager),
    playerManager(manager),
    entityManager(manager, map),
    score(manager),
    font(),
    statisticsText(),
    statisticsUpdateTime(),
    statisticsNumFrames(0),
    isMovingUp(false),
    isMovingDown(false),
    isMovingRight(false),
    isMovingLeft(false)
{
    this->window.setFramerateLimit(120);

    this->map.loadMap(mapPath);
    this->playerManager.player.setPosition(this->map.initPlayerPos);
    this->entityManager.initDiamonds(this->map.initDiamondsPos);
    this->score.init(&this->playerManager.player, &this->font, &this->window.getSize(), this->map.initDiamondsPos.size());
    this->entityManager.spawners = this->map.spawners;

    // Draw Statistic Font 
    this->font.loadFromFile("Media/Sansation.ttf");
    this->statisticsText.setFont(this->font);
    this->statisticsText.setPosition(5.f, 5.f);
    this->statisticsText.setCharacterSize(10);
}

Game::Status Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (this->window.isOpen() && this->score.getLevelStatus() == Score::Running) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;

            processEvents();
            update(TimePerFrame);
        }

        updateStatistics(elapsedTime);
        render();
    }

    return !this->window.isOpen() ? Game::Status::End : this->score.getLevelStatus() == Score::Won ? Game::Status::Next : Game::Status::Restart;
}

void Game::processEvents()
{
    sf::Event event;
    while (this->window.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;

        case sf::Event::Closed:
            this->window.close();
            break;
        }
    }
}

void Game::updatePlayerPosition(const sf::Time& elapsedTime)
{
    this->playerManager.update(this->map, this->entityManager);

    sf::Vector2f acceleration(
        this->isMovingLeft && this->isMovingRight ? 0 :
        this->isMovingLeft ? -Player::SPEED :
        this->isMovingRight ? Player::SPEED :
        0,
        0.f
    );
    ABlock_shrdp onLadder = this->playerManager.isOnLadder();
    bool jumping = false;

    if (this->isMovingUp && onLadder) {
        acceleration.y -= Player::SPEED;
    }
    if (this->isMovingDown) {
        acceleration.y += Player::SPEED;
    }

    // Prevent diagonal movements to be x + y
    if (acceleration.x && acceleration.y) {
        acceleration /= std::sqrt(2.f);
    }

    if (this->isJumping && !onLadder && this->playerManager.canJump()) {
        acceleration.y -= GRAVITY + Player::JUMP_FORCE;
        jumping = true;
    }

    this->playerManager.move(acceleration, elapsedTime, jumping);
}

void Game::update(const sf::Time& elapsedTime)
{
    this->playerManager.update(this->map, this->entityManager);
    this->updatePlayerPosition(elapsedTime);

    this->entityManager.spawnPufferfishs(elapsedTime);
    this->entityManager.updatePufferfishs(elapsedTime);

    auto diams = this->playerManager.collectDiamonds();

    if (this->playerManager.isTakingDamages(elapsedTime)) {
        this->score.removeLifePoint();
    }
    
    this->score.diamondsCollected += this->entityManager.updateDiamonds(this->playerManager.collectDiamonds());
}

void Game::render()
{
    this->window.clear();

    this->map.draw(window);
    this->entityManager.draw(window);
    this->playerManager.player.draw(window);
    this->score.draw(window);

    this->window.draw(this->statisticsText);

    this->window.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
    this->statisticsUpdateTime += elapsedTime;
    this->statisticsNumFrames += 1;

	if (this->statisticsUpdateTime >= sf::seconds(1.0f)) {
        this->statisticsText.setString(
			"Frames / Second = " + toString(this->statisticsNumFrames) + "\n" +
			"Time / Update = " + toString(this->statisticsUpdateTime.asMilliseconds() / this->statisticsNumFrames) + "ms"
        );

        this->statisticsUpdateTime -= sf::seconds(1.0f);
        this->statisticsNumFrames = 0;
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Up) {
        this->isMovingUp = isPressed;
    } else if (key == sf::Keyboard::Down) {
        this->isMovingDown = isPressed;
    } else if (key == sf::Keyboard::Left) {
        this->isMovingLeft = isPressed;
    } else if (key == sf::Keyboard::Right) {
        this->isMovingRight = isPressed;
    }
        
	if (key == sf::Keyboard::Space) {
        this->isJumping = isPressed;
	}
}
