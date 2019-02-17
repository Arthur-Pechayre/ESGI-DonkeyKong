#pragma once

class RessourcesManager
{
public:
    enum Tids
    {
        Bstonebrick,
        Bstonebrick_mossy,
        Bstonebrick_craked,
        Bair,
        Bladder,
        Bbedrock,
        Eplayer,
        Ediamond
    };

    const static std::map<RessourcesManager::Tids, std::string> T_PATHS;
    std::map<RessourcesManager::Tids, sf::Texture> T_MAP;

    RessourcesManager();
};

