#include "pch.h"
#include "PlayerManager.h"

PlayerManager::PlayerManager(const RessourcesManager& manager) :
    player(manager),
    playerSurroundings()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::updateFacing(const sf::Vector2f& movement)
{
    int prevFacing = this->player.facing;
    this->player.facing = movement.x == 0 ? this->player.facing : movement.x > 0 ? Player::FACING_RIGHT : Player::FACING_LEFT;
    this->player.facingChanged = prevFacing != this->player.facing;
}

void PlayerManager::updateSurroundings(const Map& map)
{
    this->playerSurroundings.update(this->player, map);
}

void PlayerManager::applyMovementConstraints(sf::Vector2f& movement, const sf::Time& elapsedTime)
{
    sf::FloatRect futurePos(this->player.getGlobalBounds());
    ABlock* b;

    if (movement.x > 0) { // RIGHT
        movement.x = movement.x > Player::MAX_X_SPEED ? Player::MAX_X_SPEED : movement.x;
        futurePos.left += movement.x * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingR<ASolidBlock>(futurePos);
        movement.x = !b ? movement.x : abs(b->getGlobalBounds().left - this->player.right()) / elapsedTime.asSeconds();
    }
    else if (movement.x < 0) { // LEFT
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
    }
    else if (movement.y < 0) { // TOP
        movement.y = movement.y < -Player::MAX_Y_SPEED ? -Player::MAX_Y_SPEED : movement.y;
        futurePos.top += movement.y * elapsedTime.asSeconds();

        b = this->playerSurroundings.isCollidingT<ASolidBlock>(futurePos);
        movement.y = !b ? movement.y : -1 * abs(b->getGlobalBounds().top + b->getGlobalBounds().height - this->player.top()) / elapsedTime.asSeconds();
    }
}
