#include "pch.h"
#include "Player.h"
#include "Const.h"

const float Player::SPEED = PLAYER_SPEED;
const float Player::MAX_X_SPEED = PLAYER_MAX_SPEED_X;
const float Player::MAX_Y_SPEED = PLAYER_MAX_SPEED_Y;
const float Player::JUMP_CD = PLAYER_JUMP_CD;
const int Player::JUMP_FORCE = PLAYER_JUMP_FORCE;
const float Player::DAMAGE_CD = PLAYER_DAMAGE_CD;

Player::Player(const RessourcesManager& manager) :
    AEntity(manager, RessourcesManager::Tids::Eplayer),
    jumpCooldown(sf::Time::Zero),
    damageCooldown(sf::Time::Zero),
    blinkDisplay(0),
    blinkSide(1)
{
    this->facing = AEntity::FACING_RIGHT;
}

Player::~Player()
{
}

sf::Vector2i Player::getGridPosition() const
{
    return (sf::Vector2i(round(this->left() / 32), round(this->top() / 32) + 1));
}

void Player::draw(sf::RenderWindow& w) {
    if (this->damageCooldown > sf::Time::Zero) {
        this->blinkSide *= abs(this->blinkDisplay) >= 15 ? -1 : 1;
        this->blinkDisplay += this->blinkSide;
    } else {
        this->blinkDisplay = 0;
    }
    
    if (this->blinkDisplay >= 0) {
        AEntity::draw(w);
    }
}
