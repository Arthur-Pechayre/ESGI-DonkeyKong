#include "pch.h"

#include "PufferfishEntity.h"

const float PufferfishEntity::MAX_X_SPEED = PUFFERFISH_MAX_SPEED_X;
const float PufferfishEntity::MAX_Y_SPEED = PUFFERFISH_MAX_SPEED_Y;

PufferfishEntity::PufferfishEntity(const RessourcesManager& manager) :
    AEntity(manager, RessourcesManager::Epufferfish),
    hitsRemaining(PUFFERFISH_HITS_BEFORE_DEATH)
{
    this->scale(0.80f, 0.80f);
    this->setOrigin(16, 16);
}
