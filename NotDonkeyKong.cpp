#include "pch.h"

#include "Game.h"
#include "RessourcesManager.h"
#include "Const.h"

using namespace std;

int main()
{
    RessourcesManager manager;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Not Donkey Kong 1981", sf::Style::Close + sf::Style::Resize);

    sf::Music sfm;
    if (sfm.openFromFile(RessourcesManager::M_PATHS.at(RessourcesManager::Mids::Undertale))) {
        sfm.setLoop(true);
        sfm.play();
    }
    	
    for (const auto& entry : std::experimental::filesystem::directory_iterator(MAPS_PATH)) {
        Game::Status status;
        
        std::stringstream ss;
        ss << entry.path();

        do {
            Game game(window, manager, ss.str());
            
            status = game.run();
        } while (status == Game::Restart);

        if (status == Game::End) {
            break;
        }
    }
}
