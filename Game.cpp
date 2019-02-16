#include "pch.h"
#include "Game.h"

const float Game::GRAVITY = 200;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(const RessourcesManager& manager):
    ressourcesManager(manager),
    map(manager),
    playerSurroundings(),
    window(sf::VideoMode(1024, 720), "Donkey Kong 1981", sf::Style::Close),
    player(manager),
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

    this->map.loadMap();
	this->player = Player(this->ressourcesManager);

	// Draw Statistic Font 
    this->font.loadFromFile("Media/Sansation.ttf");
    this->statisticsText.setString("Welcome to Donkey Kong 1981");
    this->statisticsText.setFont(this->font);
    this->statisticsText.setPosition(5.f, 5.f);
    this->statisticsText.setCharacterSize(10);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (this->window.isOpen()) {
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

void Game::applyMovementConstraints(sf::Vector2f& movement, const sf::Time& elapsedTime)
{
    sf::FloatRect futurePos(this->player.getGlobalBounds());
    ABlock* b;

    if (movement.x > 0) { // RIGHT
        movement.x = movement.x > Player::MAX_X_SPEED ? Player::MAX_X_SPEED : movement.x;
        futurePos.left += movement.x * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingR<ASolidBlock>(futurePos);
        movement.x = !b ? movement.x : abs(b->getGlobalBounds().left - this->player.right()) / elapsedTime.asSeconds();
    } else if (movement.x < 0) { // LEFT
        movement.x = movement.x < -Player::MAX_X_SPEED ? -Player::MAX_X_SPEED : movement.x;
        futurePos.left += movement.x * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingL<ASolidBlock>(futurePos);
        movement.x = !b ? movement.x : -1 * abs(b->getGlobalBounds().left + b->getGlobalBounds().width - this->player.left()) / elapsedTime.asSeconds();
    }
    if (movement.y > 0) { // BOT
        movement.y = movement.y > Player::MAX_Y_SPEED ? Player::MAX_Y_SPEED : movement.y;
        futurePos.top += movement.y * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingB<ASolidBlock>(futurePos);
        movement.y = !b ? movement.y : abs(b->getGlobalBounds().top - this->player.bot()) / elapsedTime.asSeconds();
    } else if (movement.y < 0) { // TOP
        movement.y = movement.y < -Player::MAX_Y_SPEED ? -Player::MAX_Y_SPEED : movement.y;
        futurePos.top += movement.y * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingT<ASolidBlock>(futurePos);
        movement.y = !b ? movement.y : -1 * abs(b->getGlobalBounds().top + b->getGlobalBounds().height - this->player.top()) / elapsedTime.asSeconds();
    }
}

void Game::update(sf::Time elapsedTime)
{
    this->playerSurroundings.update(this->player, this->map);
	sf::Vector2f movement(0.f, 0.f);

    if (this->isMovingUp /*&& isOnLadder*/) {
        movement.y -= Player::SPEED + Game::GRAVITY;
    }

    movement.y += /*isOnLadder ? 0 :*/ Game::GRAVITY;
    if (this->isMovingDown) {
        movement.y += Player::SPEED;
    }
   
    if (this->isMovingLeft) {
        movement.x -= Player::SPEED;
    }	
    if (this->isMovingRight) {
        movement.x += Player::SPEED;
    }

    this->applyMovementConstraints(movement, elapsedTime);

    int prevFacing = this->player.facing;
    this->player.facing = movement.x == 0 ? this->player.facing : movement.x > 0 ? Player::FACING_RIGHT : Player::FACING_LEFT;
    this->player.facingChanged = prevFacing != this->player.facing;
    this->player.move(movement * elapsedTime.asSeconds());
}

void Game::render()
{
    this->window.clear();

    for (int y = 0; y < this->map.tileMap.size(); ++y) {
        for (int x = 0; x < this->map.tileMap[y].size(); ++x) {
            this->window.draw(*this->map.tileMap[y][x]);
        }
	}

    for (int i = 0; i < PlayerSurroundings::Pos::BotR + 1; ++i) {
        if (!playerSurroundings.blocks[i]) {
            continue;
        }
        sf::RectangleShape rect(sf::Vector2f(32.0f, 32.0f));
        rect.setPosition(sf::Vector2f(playerSurroundings.blocks[i]->getPosition()));
        rect.setOutlineThickness(1);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Blue);

        sf::Text tx;
        tx.setString(std::to_string(i));
        tx.setFont(this->font);
        tx.setPosition(rect.getPosition() + sf::Vector2f(16.f, 16.f));
        tx.setCharacterSize(10);

        this->window.draw(rect);
        this->window.draw(tx);
    }

    if (this->player.facingChanged) {
        sf::Vector2f movement(0.f, 0.f);

        movement.x += this->player.facing * -this->player.getGlobalBounds().width;
        this->player.move(movement);
        this->player.facingChanged = false;
        this->player.scale(-1, 1);

    }

    this->window.draw(this->player);

    sf::RectangleShape rect(sf::Vector2f(this->player.getGlobalBounds().width, this->player.getGlobalBounds().height));
    rect.setPosition(sf::Vector2f(this->player.getGlobalBounds().left, this->player.getGlobalBounds().top));
    rect.setOutlineThickness(1);
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineColor(sf::Color::Yellow);
    //this->window.draw(rect);

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
    
    if (this->statisticsUpdateTime >= sf::seconds(0.050f)) {
		// Handle collision weapon enemies
	}
}

/*ABlock& Game::getPlayerFirstCollision(int entityType = -1)
{
    auto playerShape = this->player.getGlobalBounds();

    for (auto e : this->blocks) {
        auto eShape = e.getGlobalBounds();

        if ((e.m_type == entityType || entityType == -1) && eShape.intersects(playerShape)) {
            return e;
        }
    }

    return nullptr;
}*/

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
	}
}
