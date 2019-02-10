#pragma once

class RessourcesManager
{
public:
    enum Tids
    {
        Bcracked_stone_bricks,
        Eplayer
    };

    static std::map<RessourcesManager::Tids, std::string> T_PATHS;
    std::map<RessourcesManager::Tids, sf::Texture> T_MAP;

    RessourcesManager();
};

