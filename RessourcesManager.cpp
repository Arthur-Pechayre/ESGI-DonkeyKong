#include "pch.h"

#include "RessourcesManager.h"
#define ASSETS_PATH "Media/Textures"

const std::map<RessourcesManager::Tids, std::string> RessourcesManager::T_PATHS = {
    {Bstonebrick, ASSETS_PATH"/Blocks/stonebrick.png"},
    {Bstonebrick_mossy, ASSETS_PATH"/Blocks/stonebrick_mossy.png"},
    {Bstonebrick_craked, ASSETS_PATH"/Blocks/stonebrick_cracked.png"},
    {Bladder, ASSETS_PATH"/Blocks/ladder.png"},
    {Bbedrock, ASSETS_PATH"/Blocks/bedrock.png"},
    {Bpufferfish_spawner, ASSETS_PATH"/Blocks/pufferfish_spawner.png"},
    {Bair, ""},
    {Eplayer, ASSETS_PATH"/Entities/steve.png"},
    {Ediamond, ASSETS_PATH"/Entities/diamond.png"},
    {Epufferfish, ASSETS_PATH"/Entities/pufferfish.png"},
    {score_bg, ASSETS_PATH"/score_bg.png"},
};

RessourcesManager::RessourcesManager() :
    T_MAP()
{
    for (auto texture : T_PATHS) {
        T_MAP[texture.first] = sf::Texture();
        if (texture.second != "") {
            T_MAP[texture.first].loadFromFile(texture.second);
        }
    }
}
