#include "Unit.h"
#include "Unit.h"



void Unit::initVariables()
{
    this->movementSpeed = NULL;
    this->originalSpeed = NULL;
    this->currentHealth = NULL;
    this->maxHealth = NULL;
    this->AtkSpd = NULL;
    this->Atk = NULL;
    this->range = NULL;
    this->healthbar = false;
    this->friendly = true;
    this->healthbarBODY = nullptr;
}

void Unit::initBumper(bool friendly)
{
    float constY = 20;
    bumperBody.setSize(sf::Vector2f(40, this->body.getSize().y + constY));
    bumperBody.setFillColor(sf::Color::Transparent);
    if (friendly)
    {
        bumperBody.setPosition(sf::Vector2f(body.getPosition().x + body.getSize().x - bumperBody.getSize().x / 2, body.getPosition().y - constY / 2));
    }
    if (!friendly)
    {
        bumperBody.setPosition(sf::Vector2f(body.getPosition().x - bumperBody.getSize().x / 2, body.getPosition().y - constY / 2));
    }
    bumperBody.setOutlineThickness(1.25);
    bumperBody.setOutlineColor(sf::Color(255, 169, 38));
}

void Unit::initRangeBody(float range, bool friendly)
{
    float constY = 20;
    rangeBody.setSize(sf::Vector2f(range, this->body.getSize().y + constY));
    rangeBody.setFillColor(sf::Color::Transparent);
    if (friendly)
    {
        rangeBody.setPosition(sf::Vector2f(body.getPosition().x + body.getSize().x , body.getPosition().y - constY / 2));
    }
    if (!friendly)
    {
        rangeBody.setPosition(sf::Vector2f(body.getPosition().x - range, body.getPosition().y - constY / 2));
    }
    rangeBody.setOutlineThickness(1.25);
    rangeBody.setOutlineColor(sf::Color(255, 169, 60));
}

Unit::Unit(sf::String unitType, sf::Vector2f position, bool friendly)
{
    initVariables();

    //Unit type
    if (unitType == "BASE")
    {
        //Body
        body.setSize(sf::Vector2f(250, 250));
        body.setFillColor(sf::Color(100, 50, 250, 160));
       
        hitbox = body.getGlobalBounds();
        //Init Stats
        movementSpeed = 0;
        maxHealth = 10000;
        Atk = 40;
        AtkSpd = 11;
        range = 200;
        //
        this->healthbar = true;
    }

    if (unitType == "DUMMY")
    {   
        //Body
        body.setSize(sf::Vector2f(50, 100));
        body.setFillColor(sf::Color(100, 50, 250));
        hitbox = body.getGlobalBounds();
        //Init Stats
        movementSpeed = 70;
        maxHealth = 3000;
        Atk = 200;
        AtkSpd = 1.2;
        range = 0;
        //
        this->healthbar = true;
    }
    if (unitType == "DUMMY_2")
    {
        //Body
        body.setSize(sf::Vector2f(100, 120));
        body.setFillColor(sf::Color(100, 50, 250));
        hitbox = body.getGlobalBounds();
        //Init Stats
        movementSpeed = 30;
        maxHealth = 5000;
        Atk = 750;
        AtkSpd = 0.4;
        range = 0;
        //
        this->healthbar = true;
    }
    if (unitType == "Archer_DUMMY")
    {
        //Body
        body.setSize(sf::Vector2f(50, 75));
        body.setFillColor(sf::Color(100, 50, 250));
        hitbox = body.getGlobalBounds();
        //Init Stats
        movementSpeed = 70;
        maxHealth = 1200;
        Atk = 250;
        AtkSpd = 1;
        range = 500;
        //
        this->healthbar = true;
    }
   
    currentHealth = maxHealth;
    originalSpeed = movementSpeed;


    //Additional settings:
    //Fixed spawn position
    body.setPosition(sf::Vector2f(position.x, position.y - this->body.getSize().y));

    //Unit Type
    uType = unitType;

    //Healthbar
    healthbarBODY = new Healthbar(*this);

    //Bumper
    initBumper(friendly);

    //RangeBody
    initRangeBody(range, friendly);
    
    //Occupation
    if (!friendly)
    {
        movementSpeed *= -1;
        this->friendly = false;
        body.setFillColor(sf::Color::Red);
    }

}

Unit::~Unit()
{
    delete healthbarBODY;
    healthbarBODY = nullptr;
}


void Unit::render(sf::RenderWindow* window)
{
    try {
        if (this == nullptr) {
            return;
        }

        window->draw(this->body);

        if (this->healthbarBODY != nullptr)
        {
            this->healthbarBODY->render(window, this);
        }

        window->draw(this->bumperBody);
        if (range > 0)
        {
            window->draw(this->rangeBody);
        }
       
    }
    catch (std::exception& e) {
        std::cerr << "Error rendering unit: " << e.what() << std::endl;
    }
}

void Unit::move(sf::Time elapsed)
{
    body.move(this->movementSpeed * elapsed.asSeconds(), 0);
    bumperBody.move(this->movementSpeed * elapsed.asSeconds(), 0); 
    rangeBody.move(this->movementSpeed * elapsed.asSeconds(), 0);
    if (healthbarBODY != nullptr)
    {
        healthbarBODY->move(this->movementSpeed * elapsed.asSeconds(), 0);
        healthbarBODY->background.move(this->movementSpeed * elapsed.asSeconds(), 0);
    }
   
}

void Unit::moves(sf::Vector2f distance)
{
    body.move(distance);
    bumperBody.move(distance);
    rangeBody.move(distance);
    if (healthbarBODY != nullptr)
    {
        healthbarBODY->move(distance);
        healthbarBODY->background.move(distance);
    }

}

float const Unit::health() const
{
    return currentHealth;
}

float const Unit::atk() const
{
    return Atk;
}

float const Unit::atkSpd() const
{
    return AtkSpd;
}

float const Unit::range_() const
{
    return range;
}

float const Unit::speed() const
{
    return movementSpeed;
}

float const Unit::orginalSpeed_() const
{
    return originalSpeed;
}

sf::String const Unit::uType_() const
{
    return uType;
}

void Unit::fixSpeed(float value)
{
    this->movementSpeed = value;
}

void Unit::setPosiotion(sf::Vector2f position)
{
    this->body.setPosition(position);
}

sf::RectangleShape const Unit::getBody() const
{
    return body;
}

sf::FloatRect const Unit::getHitbox() const
{
    if (this != nullptr)
    {
        return hitbox;
    }
    
}

sf::FloatRect const Unit::getBumperHitbox() const
{
    return bumperHitbox;
}

sf::FloatRect const Unit::getRangeHitbox() const
{
    return rangeHitbox;
}

bool Unit::isClicked()
{
    float left = hitbox.left;
    float right = hitbox.left + hitbox.width;
    float top = hitbox.top;
    float bottom = hitbox.top + hitbox.height;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        sf::Mouse::getPosition().x >= left && sf::Mouse::getPosition().x <= right &&
        sf::Mouse::getPosition().y >= top && sf::Mouse::getPosition().y <= bottom)
    {
        return true;
    }
    return false;
}

void Unit::takeDamage(float amount)
{
    this->currentHealth -= amount;
}

void Unit::attack(Unit* target)
{
    if (atkCD.getElapsedTime().asMilliseconds() >= 1000.0f / this->AtkSpd)
    {
        target->takeDamage(this->Atk);
        this->atkCD.restart();
    }
   // else
   //{
   //    std::cout << atkCD.getElapsedTime().asMilliseconds() << " / " << 1000.0f / this->AtkSpd << std::endl;
   //}
}

float const Unit::maxHP() const
{
    return maxHealth;
}

void Unit::update(sf::Time elapsed)
{
    hitbox = body.getGlobalBounds();
    bumperHitbox = bumperBody.getGlobalBounds();
    rangeHitbox = rangeBody.getGlobalBounds();
    

    if (healthbarBODY != nullptr)
    {
        healthbarBODY->update(this);
    }
   
}
