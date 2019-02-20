#pragma once

#include "AEntity.h"
#include "Const.h"

class PufferfishEntity :
    public AEntity
{
public:
    const static int SPEED = PUFFERFISH_SPEED;
    const static float MAX_X_SPEED;
    const static float MAX_Y_SPEED;

    int hitsRemaining;

public:
    PufferfishEntity(const RessourcesManager&);
    ~PufferfishEntity() {};
};
