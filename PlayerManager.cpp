#include "pch.h"
#include "PlayerManager.h"
#include "Game.h"

PlayerManager::PlayerManager(const RessourcesManager& manager) :
    player(manager),
    playerSurroundings()
{
    this->hurtSound.setBuffer(manager.S_MAP.at(RessourcesManager::Player_hurt));
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::updateFacing()
{
    int prevFacing = this->player.facing;
    this->player.facing = this->player.velocity.x == 0 ? this->player.facing : this->player.velocity.x > 0 ? AEntity::FACING_RIGHT : AEntity::FACING_LEFT;
    this->player.facingChanged = prevFacing != this->player.facing;
}

void PlayerManager::updateJumpingCD(bool jumping, const sf::Time& elapsedTime)
{
    if (jumping) {
        this->player.jumpCooldown = sf::seconds(Player::JUMP_CD);
    } else if (this->player.jumpCooldown > sf::Time::Zero) {
        this->player.jumpCooldown -= elapsedTime;
    }
}

void PlayerManager::update(const Map& map, const EntityManager& e)
{
    this->playerSurroundings.update(this->player, map, e);
}

void PlayerManager::move(sf::Vector2f& acceleration, const sf::Time& elapsedTime, bool jumping)
{    
    this->player.velocity += acceleration;
    if (!jumping && abs(this->player.velocity.y) > Player::MAX_Y_SPEED) {
        this->player.velocity.y = this->player.velocity.y > 0 ? Player::MAX_Y_SPEED : -Player::MAX_Y_SPEED;
    }
    this->updateJumpingCD(jumping, elapsedTime);
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
        player.velocity.x = !r ? player.velocity.x : 0;
    } else if (player.velocity.x < 0) {
        player.velocity.x = !l ? player.velocity.x : 0;
    }
    if (player.velocity.y > 0) {
        player.velocity.y = !b ? player.velocity.y : abs(b->getGlobalBounds().top - this->player.bot()) / elapsedTime.asSeconds();
    }
    else if (player.velocity.y < 0) {
        player.velocity.y = !t ? player.velocity.y : -1 * abs(t->getGlobalBounds().top + t->getGlobalBounds().height - this->player.top()) / elapsedTime.asSeconds();
    }
}

ABlock_ PlayerManager::isOnLadder()
{
    return this->playerSurroundings.isOn<LadderBlock>(this->player.getGlobalBounds());
}

ABlock_ PlayerManager::isGrounded()
{
    return this->playerSurroundings.isCollidingB<ASolidBlock>(this->player.getGlobalBounds());
}

bool PlayerManager::canJump()
{
    return this->isOnLadder() == nullptr &&
        this->isGrounded() != nullptr &&
        this->player.jumpCooldown <= sf::Time::Zero;
}

void PlayerManager::applyFriction()
{
    this->player.velocity.x *= this->isGrounded() || this->isOnLadder() ? FRICTION : 1;
    this->player.velocity.y *= this->isOnLadder() ? FRICTION - 0.10 : 1;
}

void PlayerManager::applyGravity()
{
    this->player.velocity.y += this->isOnLadder() || this->isGrounded() ? 0 : GRAVITY;
}

std::vector<std::shared_ptr<DiamondEntity>> PlayerManager::collectDiamonds()
{
    return this->playerSurroundings.touchingEntities<DiamondEntity>(this->player.getGlobalBounds());
}

bool  PlayerManager::isTakingDamages(const sf::Time& elapsedTime)
{
    if (this->player.damageCooldown > sf::Time::Zero) {
        this->player.damageCooldown -= elapsedTime;

        return false;
    }
    if (this->playerSurroundings.touchingEntities<PufferfishEntity>(this->player.getGlobalBounds()).size() != 0) {
        this->player.damageCooldown = sf::seconds(Player::DAMAGE_CD);
        this->hurtSound.play();

        return true;
    } 

    return false;
}
