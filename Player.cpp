#include "pch.h"
#include "Player.h"
#include "Const.h"

const float Player::SPEED = PLAYER_SPEED;
const float Player::MAX_X_SPEED = PLAYER_MAX_SPEED_X;
const float Player::MAX_Y_SPEED = PLAYER_MAX_SPEED_Y;
const int Player::FACING_RIGHT = 1;
const int Player::FACING_LEFT = -1;

Player::Player(const RessourcesManager& manager) :
    facingChanged(false),
    facing(FACING_RIGHT),
    velocity(0, 0)
{
    this->setTexture(manager.T_MAP.at(RessourcesManager::Tids::Eplayer));
}

Player::~Player()
{
}

void Player::draw(sf::RenderWindow& w)
{
    if (this->facingChanged) {
        sf::Vector2f movement(0.f, 0.f);

        movement.x += this->facing * -this->getGlobalBounds().width;
        this->move(movement);
        this->facingChanged = false;
        this->scale(-1, 1);
    }

    w.draw(*this);
}
