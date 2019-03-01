#include "pch.h"

#include "RessourcesManager.h"

#define TEXTURES_ASSETS_PATH "Media/Textures"
#define MUSICS_ASSETS_PATH "Media/Musics"
#define SOUNDS_ASSETS_PATH "Media/Sounds"

const std::map<RessourcesManager::Tids, std::string> RessourcesManager::T_PATHS = {
    {Bstonebrick, TEXTURES_ASSETS_PATH"/Blocks/stonebrick.png"},
    {Bstonebrick_mossy, TEXTURES_ASSETS_PATH"/Blocks/stonebrick_mossy.png"},
    {Bstonebrick_craked, TEXTURES_ASSETS_PATH"/Blocks/stonebrick_cracked.png"},
    {Bladder, TEXTURES_ASSETS_PATH"/Blocks/ladder.png"},
    {Bbedrock, TEXTURES_ASSETS_PATH"/Blocks/bedrock.png"},
    {Bpufferfish_spawner, TEXTURES_ASSETS_PATH"/Blocks/pufferfish_spawner.png"},
    {Bair, ""},
    {Eplayer, TEXTURES_ASSETS_PATH"/Entities/steve.png"},
    {Ediamond, TEXTURES_ASSETS_PATH"/Entities/diamond.png"},
    {Epufferfish, TEXTURES_ASSETS_PATH"/Entities/pufferfish.png"},
    {UIscore_bg, TEXTURES_ASSETS_PATH"/UI/score_bg.png"},
    {UIheart, TEXTURES_ASSETS_PATH"/UI/heart.png"}
};

const std::map<RessourcesManager::Sids, std::string> RessourcesManager::S_PATHS = {
    {Diamond_pickup, SOUNDS_ASSETS_PATH"/coin.ogg"},
    {Player_hurt, SOUNDS_ASSETS_PATH"/player_hurt.ogg"}
};

const std::map<RessourcesManager::Mids, std::string> RessourcesManager::M_PATHS = {
    {Undertale, MUSICS_ASSETS_PATH"/undertale.ogg"}
};

RessourcesManager::RessourcesManager() :
    T_MAP(),
    S_MAP()
{
    for (auto texture : T_PATHS) {
        T_MAP[texture.first] = sf::Texture();
        if (texture.second != "") {
            T_MAP[texture.first].loadFromFile(texture.second);
        }
    }

    for (auto sound : S_PATHS) {
        S_MAP[sound.first] = sf::SoundBuffer();
        S_MAP[sound.first].loadFromFile(sound.second);
    }
}
