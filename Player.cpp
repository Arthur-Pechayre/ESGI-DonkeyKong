#include "pch.h"
#include "Player.h"

const float Player::MAX_X_SPEED = 150;
const float Player::MAX_Y_SPEED = 200;
const int Player::FACING_RIGHT = 1;
const int Player::FACING_LEFT = -1;

Player::Player(const RessourcesManager& manager):
sf::Sprite(),
_feetHitBox(),
_facingChanged(false),
_facing(FACING_RIGHT)
{
    this->setTexture(manager.T_MAP.at(RessourcesManager::Tids::Eplayer));
    _feetHitBox.setSize(sf::Vector2f(this->getGlobalBounds().width, 1));
    this->updateHitboxes();
}

Player::~Player()
{
}

void Player::updateHitboxes()
{
    sf::FloatRect playerShape = this->getGlobalBounds();

    _feetHitBox.setPosition(playerShape.left, playerShape.top + playerShape.height);
}
