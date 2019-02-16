#include "pch.h"
#include "Map.h"

Map::Map(const RessourcesManager& manager) :
    ressourcesManager{&manager}
{
}

void Map::loadMap()
{
    auto bg = BlockGenerator();

    std::vector<std::string> map = {
        "                ",
        "                ",
        "            ssss",
        "      ssss      ",
        "ssss            ",
        "            ssss",
        "      ssss      ",
        "ssss            ",
        "            ssss",
        "      ssss      ",
        "ssss            ",
        "            ssss",
        "      ssss      ",
        "ssss            ",
        "ssssssssssssssss"
    };

    int xmax = 0;
    for (int y = 0; y < map.size(); ++y) {
        std::vector<ABlock*> b;
        ++this->size.x;
        
        for (int x = 0; x < map[y].size(); ++x) {
            ABlock* _block = bg.CreateBlock(map[y][x], *ressourcesManager);
            _block->setPosition((float)(x * 32), (float)(y * 32));

            //CreateCharacterAndObject(readedLine.c_str()[column], _block);
            b.insert(b.end(), _block);

            xmax = x > xmax ? x : xmax;
        }
        this->tileMap.insert(this->tileMap.end(), b);
    }
    this->size.x = xmax;
    this->size.y = map.size();

    // Draw Echelles

    /*_TextureEchelle.loadFromFile("Media/Textures/Echelle.png");

    for (int i = 0; i < ECHELLE_COUNT; i++)
    {
        _Echelle[i].setTexture(_TextureEchelle);
        _Echelle[i].setPosition(100.f + 70.f * (i + 1), 0.f + BLOCK_SPACE * (i + 1) + _sizeBlock.y );

        std::shared_ptr<Entity> se = std::make_shared<Entity>();
        se->m_sprite = _Echelle[i];
        se->m_type = EntityType::echelle;
        se->m_size = _TextureEchelle.getSize();
        se->m_position = _Echelle[i].getPosition();
        EntityManager::m_Entities.push_back(se);
    }*/
}
