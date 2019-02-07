#include "pch.h"
#include "Player.h"

const float Player::MAX_X_SPEED = 150;
const float Player::MAX_Y_SPEED = 200;
const int Player::FACING_RIGHT = 1;
const int Player::FACING_LEFT = -1;

Player::Player() :
_facingChanged(false)
{
    sf::CircleShape circle(1);
    _feetHitBox = circle;
    _facing = FACING_RIGHT;
    this->updateHitboxes();
}

Player::~Player()
{
}

bool Player::grounded(std::vector<std::shared_ptr<Entity>> blocks)
{
    for (auto block : blocks) {
        if (block->m_type == EntityType::block && block->m_sprite.getGlobalBounds().intersects(_feetHitBox.getGlobalBounds())) {
            return true;
        }
    }

    return false;
}

void Player::updateHitboxes()
{
    sf::FloatRect playerShape = m_sprite.getGlobalBounds();
    _feetHitBox.setPosition((playerShape.left + playerShape.width / 2) - 1, (playerShape.top + playerShape.height) - 6);
}
