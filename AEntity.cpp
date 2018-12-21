#include "pch.h"
#include "AEntity.hh"

AEntity::AEntity(size_t x, size_t y, char d)
{
}

AEntity::~AEntity()
{
}

void AEntity::setX(size_t x)
{
    _x = x;
}

void AEntity::setY(size_t y)
{
    _y = y;
}

size_t AEntity::getX() const
{
    return size_t();
}

size_t AEntity::getY() const
{
    return size_t();
}

char AEntity::getDirection() const
{
    return _direction;
}
