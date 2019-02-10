#pragma once

#include "ABlock.h"
#include "CrackedStoneBrickBlock.h"
#include <map>
#include <functional>

class BlockGenerator
{
private:
    int _errorCount = 0;
    std::map<char, std::function<ABlock*(int, int)>> _blocks;

    template<typename BlockType>
    void    RegisterBlock(const char& c)
    {
        this->_blocks[c] = [](int x, int y) {
            return (new BlockType(x, y));
        };
    }

public:
    BlockGenerator()
    {
        this->RegisterBlock<CrackedStoneBrickBlock>('s');
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

    ABlock*     CreateBlock(const char& c, int x, int y)
    {
        ABlock*     block;

        try {
            block = this->_blocks[c](x, y);
        } catch (const std::bad_function_call& e) {
            ++_errorCount;
            block = nullptr;
        }

        return (block);
    };
};
