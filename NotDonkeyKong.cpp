#include "pch.h"

#include "Game.h"
#include "RessourcesManager.h"

int main()
{
    RessourcesManager manager;

    std::string s;
    std::cout << "Please enter an absolute path to maps folder : ";
    std::cin >> s;
    	
    for (const auto& entry : std::experimental::filesystem::directory_iterator(s)) {
        Game::Status status;

        std::stringstream ss;
        ss << entry.path();

        do {
            Game game(manager, ss.str());
            
            status = game.run();
        } while (status == Game::Restart);

        if (status == Game::End) {
            break;
        }
    }
}
