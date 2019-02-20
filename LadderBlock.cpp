#include "pch.h"
#include "LadderBlock.h"

LadderBlock::LadderBlock(const RessourcesManager& manager, const char&, const sf::Vector2f& pos) :
    ABlock(manager, RessourcesManager::Tids::Bladder, pos)
{
}
