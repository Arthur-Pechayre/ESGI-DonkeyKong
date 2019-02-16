#include "pch.h"
#include "Player.h"

const float Player::SPEED = 150;
const float Player::MAX_X_SPEED = 150;
const float Player::MAX_Y_SPEED = 200;
const int Player::FACING_RIGHT = 1;
const int Player::FACING_LEFT = -1;

Player::Player(const RessourcesManager& manager):
sf::Sprite(),
facingChanged(false),
facing(FACING_RIGHT)
{
    this->setTexture(manager.T_MAP.at(RessourcesManager::Tids::Eplayer));
}

Player::~Player()
{
}

float Player::width() const
{
    return this->getGlobalBounds().width;
}

float Player::height() const
{
    return this->getGlobalBounds().height;
}

float Player::top() const
{
    return this->getGlobalBounds().top;
}

float Player::bot() const
{
    return this->getGlobalBounds().top + this->height();
}

float Player::left() const
{
    return this->getGlobalBounds().left;
}

float Player::right() const
{
    return this->getGlobalBounds().left + this->width();
}
