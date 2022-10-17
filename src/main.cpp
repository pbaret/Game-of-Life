#include <SFML/Graphics.hpp>
#include "global.h"
#include "game_manager.h"
#include <iostream>

using namespace gol;

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(scale * width, scale * height)), "SFML Game Of Life");
    window.setFramerateLimit(15);    // no framerate limit

    GameManager game_manager(&window);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        game_manager.ProcessUserInputs();

        game_manager.UpdateGameState();

        game_manager.UpdateDisplay();
    }

    return 0;
}