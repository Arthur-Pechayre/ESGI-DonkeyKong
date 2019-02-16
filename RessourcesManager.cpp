#include "pch.h"

#include "RessourcesManager.h"
#define ASSETS_PATH "Media/Textures"

const std::map<RessourcesManager::Tids, std::string> RessourcesManager::T_PATHS = {
    {Bstonebrick, ASSETS_PATH"/Blocks/stonebrick.png"},
    {Bstonebrick_mossy, ASSETS_PATH"/Blocks/stonebrick_mossy.png"},
    {Bstonebrick_craked, ASSETS_PATH"/Blocks/stonebrick_cracked.png"},
    {Bair, ""},
    {Eplayer, ASSETS_PATH"/Entities/steve.png"}
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
