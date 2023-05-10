#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
class Button : public sf::RectangleShape
{
private:
	//Hitbox for mouse click for button
	sf::FloatRect hitbox;
	//Function that initialize variables
	void initVariables();

public:
	//Constructor
	Button();
	Button(sf::Vector2f position, sf::Vector2f size, sf::Color color);

	//Function that returns true if user click in the button object
	bool isClicked();

	//Update button logic
	void update();

	//Renders button on screen
	void render(sf::RenderWindow* window);

};

