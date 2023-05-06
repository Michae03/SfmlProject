#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameEngine.h"

//Init Game engine
GameEngine game;

int main()
{
    std::cout << "V0.4.2 is working" << std::endl;
    //Game loop
    while (game.running())
    {

        //Update game logic
        game.update();
        //Render game graphic
        game.render();

    }

    return 0;
}





















