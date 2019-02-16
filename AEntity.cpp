#include "pch.h"
#include "AEntity.h"

AEntity::AEntity() :
    sf::Sprite()
{
}

void AEntity::draw(sf::RenderWindow& w)
{
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
