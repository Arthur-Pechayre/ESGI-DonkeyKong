#include "pch.h"
#include "Player.h"
#include "Const.h"

const float Player::SPEED = PLAYER_SPEED;
const float Player::MAX_X_SPEED = PLAYER_MAX_SPEED_X;
const float Player::MAX_Y_SPEED = PLAYER_MAX_SPEED_Y;
const float Player::JUMP_CD = PLAYER_JUMP_CD;
const int Player::JUMP_FORCE = PLAYER_JUMP_FORCE;
const int Player::FACING_RIGHT = 1;
const int Player::FACING_LEFT = -1;

Player::Player(const RessourcesManager& manager) :
    AEntity(manager, RessourcesManager::Tids::Eplayer),
    facingChanged(false),
    facing(FACING_RIGHT),
    velocity(0, 0),
    jumpCooldown(sf::Time::Zero)
{
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
