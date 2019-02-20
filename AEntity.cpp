#include "pch.h"

#include "AEntity.h"

AEntity::AEntity(const RessourcesManager& manager, const RessourcesManager::Tids& tid) :
    sf::Sprite(),
    facing(AEntity::FACING_LEFT),
    facingChanged(false),
    velocity(0, 0),
    _tid(tid)
{
    this->setTexture(manager.T_MAP.at(this->_tid));
}

void AEntity::draw(sf::RenderWindow& w)
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

float AEntity::width() const
{
    return this->getGlobalBounds().width;
}

float AEntity::height() const
{
    return this->getGlobalBounds().height;
}

float AEntity::top() const
{
    return this->getGlobalBounds().top;
}

float AEntity::bot() const
{
    return this->getGlobalBounds().top + this->height();
}

float AEntity::left() const
{
    return this->getGlobalBounds().left;
}

float AEntity::right() const
{
    return this->getGlobalBounds().left + this->width();
}

sf::Vector2i AEntity::getGridPosition() const
{
    return (sf::Vector2i(round(this->left() / 32), round(this->top() / 32)));
}
