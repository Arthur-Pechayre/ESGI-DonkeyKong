#pragma once

#include "pch.h"
#include <map>
#include <functional>

#include "ABlock.h"
#include "StonebrickBlock.h"
#include "AirBlock.h"
#include "LadderBlock.h"
#include "BedrockBlock.h"

class BlockGenerator
{
private:
    int _errorCount = 0;
    std::map<char, std::function<ABlock*(const RessourcesManager&)>> _blocks;

    template<typename BlockType>
    void    RegisterBlock(const char& c)
    {
        this->_blocks[c] = [](const RessourcesManager& manager) {
            return (new BlockType(manager));
        };
    }

public:
    BlockGenerator()
    {
        // Entities spawn blocks
        this->RegisterBlock<AirBlock>('P'); // Player
        this->RegisterBlock<AirBlock>('c'); // Diamond

        this->RegisterBlock<StonebrickBlock>('s');
        this->RegisterBlock<BedrockBlock>(0);
        this->RegisterBlock<LadderBlock>('l');
        this->RegisterBlock<AirBlock>(' ');
    }

    ~BlockGenerator()
    {
        this->_blocks.clear();
    };

    int GetErrorCount()
    {
        int cnt = this->_errorCount;
        _errorCount = 0;

        return cnt;
    }

    ABlock* CreateBlock(const char& c, const RessourcesManager& manager)
    {
        ABlock* block;
        
        try {
            block = this->_blocks[c](manager);
        } catch (const std::bad_function_call& e) {
            ++_errorCount;
            block = nullptr;
        }

        return (block);
    };
};
