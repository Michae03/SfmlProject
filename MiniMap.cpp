#include "MiniMap.h"

MiniMap::MiniMap()
{
}

MiniMap::MiniMap(float topBoundarg, float rightBoundarg, float bottomBoundarg, float leftBoundarg)
{
	scaleX = 0.1;
	scaleY = 0.1;
	this->setSize(sf::Vector2f((rightBoundarg + 150 - leftBoundarg) * scaleX, (bottomBoundarg - topBoundarg) * scaleY));
	this->setPosition(sf::Vector2f(1900 - this->getSize().x, 10));
	this->setFillColor(sf::Color(232, 220, 220, 60));
	this->setOutlineThickness(0.5);
	this->setOutlineColor(sf::Color::Black);
	topBound = topBoundarg;
	rightBound = rightBoundarg;
	bottomBound = bottomBoundarg;
	leftBound = leftBoundarg;
	currentPosition.setSize(sf::Vector2f(1920 * scaleX, this->getSize().y));
	currentPosition.setPosition(this->getPosition());
	currentPosition.setFillColor(sf::Color::Transparent);
	currentPosition.setOutlineThickness(1);
	currentPosition.setOutlineColor(sf::Color::Black);
}

void MiniMap::renderUnitsOnMiniMap(std::vector<Unit*> units, sf::RenderWindow* window, float offset)
{
	using namespace std;
	window->draw(*this);
	
	for (auto it = units.begin(); it != units.end(); ++it)
	{
		if (*it != nullptr)
		{
			sf::RectangleShape dot;
			bool friendly = (*it)->friendly;
			dot.setSize(sf::Vector2f((*it)->getBody().getSize().x * scaleX, (*it)->getBody().getSize().y * scaleY));
			dot.setPosition(sf::Vector2f(this->getPosition().x - scaleX * offset + scaleX * ((*it)->getBody().getPosition().x - leftBound), this->getPosition().y + this->getSize().y - scaleY * (*it)->getBody().getSize().y ));
			
			if (friendly)
			{
				dot.setFillColor(sf::Color::Blue);
			}
			else
			{
				dot.setFillColor(sf::Color::Red);
			}
			window->draw(dot);
		}
	}
	
}

void MiniMap::render(std::vector<Unit*> units, sf::RenderWindow* window, float offset)
{
	renderUnitsOnMiniMap(units, window, offset);
	window->draw(currentPosition);;
}

void MiniMap::update(float constPointZero)
{
	currentPosition.setPosition(this->getPosition());
	currentPosition.setPosition(sf::Vector2f(-constPointZero * scaleX + currentPosition.getPosition().x, currentPosition.getPosition().y));
}
