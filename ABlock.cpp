#include "pch.h"
#include "ABlock.h"

ABlock::ABlock(const RessourcesManager& manager, const RessourcesManager::Tids& tid) :
sf::Sprite(),
_tid(tid)
{
    this->setTexture(manager.T_MAP.at(this->_tid));
}
