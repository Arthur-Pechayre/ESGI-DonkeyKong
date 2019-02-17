#pragma once

#include "ABlock.h"
#include "ASolidBlock.h"

class BedrockBlock : public ABlock, virtual public ASolidBlock
{
public:
    BedrockBlock(const RessourcesManager&);
    ~BedrockBlock() {};
};

