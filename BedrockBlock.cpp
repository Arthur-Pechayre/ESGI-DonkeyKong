#include "pch.h"

#include "BedrockBlock.h"

BedrockBlock::BedrockBlock(const RessourcesManager& manager, const char&, const sf::Vector2f& pos) :
    ABlock(manager, RessourcesManager::Tids::Bbedrock, pos)
{
}
