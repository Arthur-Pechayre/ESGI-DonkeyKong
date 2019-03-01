#pragma once

class RessourcesManager
{
public:
    // Textures 
    enum Tids
    {
        Bstonebrick,
        Bstonebrick_mossy,
        Bstonebrick_craked,
        Bair,
        Bladder,
        Bbedrock,
        Bpufferfish_spawner,
        Eplayer,
        Ediamond,
        Epufferfish,
        UIscore_bg,
        UIheart
    };
    const static std::map<RessourcesManager::Tids, std::string> T_PATHS;
    std::map<RessourcesManager::Tids, sf::Texture> T_MAP;

    // Sounds
    enum Sids
    {
        Diamond_pickup,
        Player_hurt
    };
    const static std::map<RessourcesManager::Sids, std::string> S_PATHS;
    std::map<RessourcesManager::Sids, sf::SoundBuffer> S_MAP;

    // Musics
    enum Mids
    {
        Undertale
    };
    const static std::map<RessourcesManager::Mids, std::string> M_PATHS;

    RessourcesManager();
};

