#include "pch.h"
#include "Player.h"

Player::Player()
{
    sf::CircleShape circle(1);
    _feetHitBox = circle;
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
