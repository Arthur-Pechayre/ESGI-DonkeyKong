#include "pch.h"
#include "Map.h"

Map::Map(const RessourcesManager& manager) :
    ressourcesManager{&manager},
    initializersMap(),
    size(0, 0)
{
    this->initializersMap.insert(std::pair<char, EntityPositionInitializer>('P', &Map::initPlayerOnBlock));
}

void Map::draw(sf::RenderWindow& w)
{
    for (int y = 0; y < this->tileMap.size(); ++y) {
        for (int x = 0; x < this->tileMap[y].size(); ++x) {
            w.draw(*this->tileMap[y][x]);
        }
    }
}

void Map::loadMap()
{
    auto bg = BlockGenerator();

    std::vector<std::string> map = {
        "                ",
        "    l           ",
        "ssssl           ",
        "    l    P      ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    lssss  s ss ",
        "    l           ",
        "    l           ",
        "    l           ",
        "    l  ss       ",
        "ssssssssssssssss",
    };

    this->size.y = map.size();
    for (int y = 1; y < map.size() + 1; ++y) {
        std::vector<ABlock*> b;
        
        for (int x = 1; x < map[y - 1].size() + 1; ++x) {
            ABlock* neoBlock = bg.CreateBlock(map[y - 1][x - 1], *ressourcesManager);

            neoBlock->setPosition((float)(x * 32), (float)(y * 32));
            this->initEntitiesPositions(map[y - 1][x - 1], neoBlock);
            
            b.insert(b.end(), neoBlock);
            this->size.x = this->size.x < map[y - 1].size() ? map[y - 1].size() : this->size.x;
        }
        this->tileMap.insert(this->tileMap.end(), b);
    }

    this->size.y += 2;
    this->size.x += 2;
    for (int y = 0; y < this->size.y; ++y) {
        if (y == 0 || y == this->size.y - 1) {
            std::vector<ABlock*> b;
            for (int x = 0; x < this->size.x; ++x) {
                ABlock* neoBlock = bg.CreateBlock(0, *ressourcesManager);
                neoBlock->setPosition((float)(x * 32), (float)(y * 32));

                b.insert(b.end(), neoBlock);
            }
            this->tileMap.insert(y == 0 ? this->tileMap.begin() : this->tileMap.end(), b);
        } else {
            this->tileMap[y].insert(this->tileMap[y].begin(), bg.CreateBlock(0, *ressourcesManager));
            this->tileMap[y].insert(this->tileMap[y].end(), bg.CreateBlock(0, *ressourcesManager));
            this->tileMap[y][0]->setPosition((float)(0), (float)(y * 32));
            this->tileMap[y][this->tileMap[y].size() - 1]->setPosition((float)((this->tileMap[y].size() - 1) * 32), (float)(y * 32));
        }
    }

    
}

void Map::initPlayerOnBlock(const ABlock* block)
{
    this->initPlayerPos = block->getPosition();
    ++this->initPlayerPos.y;
}

void Map::initEntitiesPositions(const char& c, const ABlock* block)
{
    std::map<char, EntityPositionInitializer>::iterator pos;
    pos = this->initializersMap.find(c);
    if (pos != initializersMap.end()) {
        (this->*pos->second)(block);
    }
}
