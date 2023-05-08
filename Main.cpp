#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GameEngine.h"

//Init Game engine
GameEngine game;

int main()
{
<<<<<<< HEAD
    std::cout << "V0.5 is working" << std::endl;
=======
    std::cout << "V0.4.7 is working" << std::endl;
>>>>>>> main
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





















