#include "pch.h"

#include "AirBlock.h"

AirBlock::AirBlock(const RessourcesManager& manager) :
    ABlock(manager, RessourcesManager::Tids::Bair)
{
}

AirBlock::~AirBlock()
{
}
