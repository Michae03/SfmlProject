#pragma once
#include "Healthbar.h"
class LoadingBar : public sf::RectangleShape
{
private:

public:
	sf::RectangleShape background;
	LoadingBar();
	LoadingBar(sf::Vector2f size, sf::Vector2f position);
	void update(float nominator, float denominator);
	void render(sf::RenderWindow* window);
};

