#include "LoadingBar.h"

LoadingBar::LoadingBar()
{
    background.setSize(sf::Vector2f(0, 0));
    background.setFillColor(sf::Color::Black);
    background.setPosition(0, 0);
    background.setOutlineThickness(2.2);
    background.setOutlineColor(sf::Color::Black);
    this->setSize(background.getSize());
    this->setFillColor(sf::Color::Green);
    this->setPosition(background.getPosition());
}

LoadingBar::LoadingBar(sf::Vector2f size, sf::Vector2f position)
{
    background.setSize(size);
    background.setFillColor(sf::Color::Black);
    background.setPosition(position);
    background.setOutlineThickness(2.2);
    background.setOutlineColor(sf::Color::Black);
    this->setSize(background.getSize());
    this->setFillColor(sf::Color::Green);
    this->setPosition(background.getPosition());
}

void LoadingBar::update(float nominator, float denominator)
{
    if (nominator >= denominator)
    {
        this->setSize(this->background.getSize());
        this->setFillColor(sf::Color::Green);
    }
    else
    {
        this->setSize(sf::Vector2f((nominator / denominator) * this->background.getSize().x, background.getSize().y));
        this->setFillColor(sf::Color::Red);
    }
}

void LoadingBar::render(sf::RenderWindow* window)
{
    window->draw(this->background);
    window->draw(*this);
}
