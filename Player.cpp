#include "pch.h"
#include "Player.hh"
#include "Player.h"

Player::Player()
{
    auto playerShape = m_sprite.getGlobalBounds();
    float feetX = playerShape.left + playerShape.width / 2;
    float feetY = playerShape.top + playerShape.height;

    sf::CircleShape circle(1);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1);
    circle.setPosition(feetX - 1, feetY - 6);

    _feetHitBox = circle;
}

Player::~Player()
{
}

bool Player::grounded() {
    auto playerShape = _sprite.getGlobalBounds();
    float feetX = playerShape.left + playerShape.width / 2;
    float feetY = playerShape.top + playerShape.height;

    sf::CircleShape circle(1);
    circle.setOutlineColor(sf::Color::Red);
    circle.setOutlineThickness(1);
    circle.setPosition(feetX - 1, feetY - 6);

    return false;
}
