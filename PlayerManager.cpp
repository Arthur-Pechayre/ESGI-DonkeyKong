#include "pch.h"
#include "PlayerManager.h"
#include "Game.h"

PlayerManager::PlayerManager(const RessourcesManager& manager) :
    player(manager),
    playerSurroundings()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::updateFacing()
{
    int prevFacing = this->player.facing;
    this->player.facing = this->player.velocity.x == 0 ? this->player.facing : this->player.velocity.x > 0 ? Player::FACING_RIGHT : Player::FACING_LEFT;
    this->player.facingChanged = prevFacing != this->player.facing;
}

void PlayerManager::updateSurroundings(const Map& map)
{
    this->playerSurroundings.update(this->player, map);
}

void PlayerManager::move(sf::Vector2f& acceleration, const sf::Time& elapsedTime, bool jumping)
{    
    this->player.velocity += acceleration;
    if (!jumping && abs(this->player.velocity.y) > Player::MAX_Y_SPEED) {
        this->player.velocity.y = this->player.velocity.y > 0 ? Player::MAX_Y_SPEED : -Player::MAX_Y_SPEED;
    }
    this->applyGravity();
    this->applyFriction();
    this->handleCollisions(elapsedTime);
    if (abs(this->player.velocity.x) > Player::MAX_X_SPEED) {
        this->player.velocity.x = this->player.velocity.x > 0 ? Player::MAX_X_SPEED : -Player::MAX_X_SPEED;
    }

    this->updateFacing();
    this->player.move(player.velocity * elapsedTime.asSeconds());
}

void PlayerManager::handleCollisions(const sf::Time& elapsedTime)
{
    sf::FloatRect futurePos(this->player.getGlobalBounds());
    futurePos.left += player.velocity.x * elapsedTime.asSeconds();
    futurePos.top += player.velocity.y * elapsedTime.asSeconds();

    auto t = this->playerSurroundings.isCollidingT<ASolidBlock>(futurePos);
    auto b = this->playerSurroundings.isCollidingB<ASolidBlock>(futurePos);
    auto l = this->playerSurroundings.isCollidingL<ASolidBlock>(futurePos);
    auto r = this->playerSurroundings.isCollidingR<ASolidBlock>(futurePos);

    if (player.velocity.x > 0) {
        player.velocity.x = !r ? player.velocity.x : abs(r->getGlobalBounds().left - this->player.right()) / elapsedTime.asSeconds();
    } else if (player.velocity.x < 0) {
        player.velocity.x = !l ? player.velocity.x : -1 * abs(l->getGlobalBounds().left + l->getGlobalBounds().width - this->player.left()) / elapsedTime.asSeconds();
    }
    if (player.velocity.y > 0) {
        player.velocity.y = !b ? player.velocity.y : abs(b->getGlobalBounds().top - this->player.bot()) / elapsedTime.asSeconds();
    }
    else if (player.velocity.y < 0) {
        player.velocity.y = !t ? player.velocity.y : -1 * abs(t->getGlobalBounds().top + t->getGlobalBounds().height - this->player.top()) / elapsedTime.asSeconds();
    }
}

ABlock* PlayerManager::isOnLadder()
{
    return this->playerSurroundings.isOn<LadderBlock>(this->player.getGlobalBounds());
}

ABlock* PlayerManager::isGrounded()
{
    return this->playerSurroundings.isCollidingB<ASolidBlock>(this->player.getGlobalBounds());
}

void PlayerManager::applyFriction()
{
    this->player.velocity.x *= this->isGrounded() || this->isOnLadder() ? 0.84 : 1;
    this->player.velocity.y *= this->isOnLadder() ? 0.75 : 1;
}

void PlayerManager::applyGravity()
{
    this->player.velocity.y += this->isOnLadder() ? 0 : Game::GRAVITY;
}
