#include "Healthbar.h"
#include "Unit.h"


Healthbar::Healthbar(const Unit& u) : unit(u)
{
    background.setSize(sf::Vector2f(unit.getBody().getSize().x, 10));
    background.setFillColor(sf::Color::Red);
    background.setPosition(sf::Vector2f(unit.getBody().getPosition().x, unit.getBody().getPosition().y - 25));
    background.setOutlineThickness(2.2);
    background.setOutlineColor(sf::Color::Black);
    this->setSize(background.getSize());
    this->setFillColor(sf::Color::Green);
    this->setPosition(background.getPosition());
}


void Healthbar::update(const Unit* unit)
{
    this->setSize(sf::Vector2f(unit->health() / unit->maxHP() * background.getSize().x, background.getSize().y));
}

void Healthbar::render(sf::RenderWindow* window, const Unit* unit)
{
        window->draw(this->background);
        window->draw(*this);
  
}