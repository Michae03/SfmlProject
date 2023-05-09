#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Unit.h"
class MiniMap : public sf::RectangleShape
{
private:
	float topBound;
	float rightBound;
	float bottomBound;
	float leftBound;
	float scaleX;
	float scaleY;
	sf::RectangleShape currentPosition;

public:
	MiniMap();
	//Constructor, arguments are bounds of playable map
	MiniMap(float topBound, float rightBound, float bottomBound, float leftBound);

	//renders units on map as small rectangles
	void renderUnitsOnMiniMap(std::vector<Unit*> units, sf::RenderWindow* window, float offset);

	//renders current position on map
	void render(std::vector<Unit*> units, sf::RenderWindow* window, float offset = 1);

	//Updates logic so object wont run beside minimap, argument have to be object that starts at zero X nad moves with camera 
	void update(float constPointZero);
};

