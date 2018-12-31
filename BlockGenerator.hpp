#pragma once

#include "StoneBlock.hh"
#include "ABlock.hh"
#include <map>
#include <functional>

class BlockGenerator
{
private:
    std::map<char, std::function<ABlock*(int, int)>> _blocks;
    int _errorCount = 0;

    template<typename BlockType>
    void    RegisterBlock(const char& c)
    {
        this->_blocks[c] = [](int x, int y) {
            return (new BlockType(x, y));
        };
    }

public:
    int GetErrorCount() const
    {
        int cnt = this->_errorCount;
        this->_errorCount = 0;

        return cnt;
    }

    BlockGenerator()
    {
        this->RegisterBlock<AirBlock>(' ');
        this->RegisterBlock<StoneBlock>('s');
    }

    ~BlockGenerator()
    {
        this->_blocks.clear();
    };

    ABlock*     CreateBlock(const char& c, int x, int y)
    {
        ABlock*     block;

        try {
            block = this->_blocks[c](x, y);
        } catch (const std::bad_function_call& e) {
            ++_errorCount;
            block = this->_blocks[' '](x, y);
        }

        return (block);
    };
};
