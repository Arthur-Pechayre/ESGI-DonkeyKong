#include "pch.h"
#include "ABlock.h"

ABlock::ABlock(const RessourcesManager& manager, const RessourcesManager::Tids& tid) :
sf::Sprite(),
TID(tid)
{
    this->setTexture(manager.T_MAP.at(this->TID));
}
