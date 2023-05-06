#include "Button.h"

void Button::initVariables()
{
    hitbox = this->getGlobalBounds();
}

Button::Button()
{
    initVariables();
}

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
    this->setPosition(position);
    this->setSize(size);
    this->setFillColor(color);
}

bool Button::isClicked()
{
    float left = hitbox.left;
    float right = hitbox.left + hitbox.width;
    float top = hitbox.top;
    float bottom = hitbox.top + hitbox.height;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition().x >= left && sf::Mouse::getPosition().x <= right &&
        sf::Mouse::getPosition().y >= top && sf::Mouse::getPosition().y <= bottom )
    {
        return true;
    }
    return false;
}

void Button::update()
{
    hitbox = this->getGlobalBounds();
}

void Button::render(sf::RenderWindow* window)
{
    window->draw(*this);
}
