#pragma once
#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Unit; // forward declaration

class Healthbar : public sf::RectangleShape
{
private:
   
    const Unit& unit; // referencja do klasy Unit

public:
    sf::RectangleShape background;
    Healthbar(const Unit& u);
    void update(const Unit* unit);
    void render(sf::RenderWindow* window, const Unit* unit);
};

#endif // HEALTHBAR_H