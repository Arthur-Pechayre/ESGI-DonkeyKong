#include "pch.h"

#include "AirBlock.h"

AirBlock::AirBlock(const RessourcesManager& manager, const char&, const sf::Vector2f& pos) :
    ABlock(manager, RessourcesManager::Tids::Bair, pos)
{
}

AirBlock::~AirBlock()
{
}
