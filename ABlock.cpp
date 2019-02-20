#include "pch.h"
#include "ABlock.h"

ABlock::ABlock(const RessourcesManager& manager, const RessourcesManager::Tids& tid, const sf::Vector2f& pos) :
sf::Sprite(),
_tid(tid)
{
    this->setTexture(manager.T_MAP.at(this->_tid));
    this->setPosition(pos);
}
