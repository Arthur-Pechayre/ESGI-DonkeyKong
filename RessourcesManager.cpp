#include "pch.h"

#include "RessourcesManager.h"

std::map<RessourcesManager::Tids, std::string> RessourcesManager::T_PATHS = {
    {Bcracked_stone_bricks, "Media/Textures/Block.png"},
    {Eplayer, "Media/Textures/Mario_small_transparent.png"}
};

RessourcesManager::RessourcesManager() :
    T_MAP()
{
    for (auto texture : T_PATHS) {
        T_MAP[texture.first] = sf::Texture();
        T_MAP[texture.first].loadFromFile(texture.second);

        /*
        auto& neo = new std::pair<Textures::Tids, sf::Texture> neo();
        neo.first = texture.first;
        neo.second = sf::Texture();
        neo.second.loadFromFile(texture.second);

        map.insert(neo);
        */
    }
}
