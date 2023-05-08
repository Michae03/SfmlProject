#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Healthbar.h"



//Class that manage unit logic

class Unit
{
protected:
	//Unit type
	sf::String uType;

	//Unit "body"
	sf::RectangleShape body;

	//HITBOX:
	
	//Unit hitbox
	sf::RectangleShape bumperBody;
	sf::FloatRect hitbox;
	sf::FloatRect bumperHitbox;
	sf::RectangleShape rangeBody;
	sf::FloatRect rangeHitbox;
	
	
	
	// UNIT STATS:
	
	//Velocity which unit travel
	float movementSpeed;
	float originalSpeed;
	
	float maxHealth;
	
	float Atk;
	//Attack Spped in Attacks per second
	float AtkSpd;

	float range;

	

	
	//Healthbar body
	Healthbar* healthbarBODY;
	
	//CurrentHealth
	float currentHealth;

	//Attack Speed Timer
	sf::Clock atkCD;

	//Function that initialize variables
	void initVariables();

	//Function that initialize bumper
	void initBumper(bool friendly);

	//Function that initialize range attack body
	void initRangeBody(float range, bool friendly);
public:

	//Does it have healthbar (basicly every unit)
	bool healthbar;
	//Occupation
	bool friendly;

	//Constructor that creates specific unit
	Unit(sf::String unitType, sf::Vector2f position, bool friendly);

	//Destructor
	~Unit();

	//Function that update Unit logic ex. hitboxes, death status
	void update(sf::Time elapsed);

	//Funcion that render sprites
	void render(sf::RenderWindow* window);

	//Funcion that keeps unit moving
	void move(sf::Time elapsed);

	//Function that returns body of a Unit
	sf::RectangleShape  const getBody() const;

	//Function that returns hitbox of a Unit
	sf::FloatRect const getHitbox() const;

	//Function that returns hitbox of a Bumper
	sf::FloatRect const getBumperHitbox() const;

	//Function that returns hitbox of a archerBody
	sf::FloatRect const getRangeHitbox() const;

	//Function that returns true if user click on the unit
	bool isClicked();

	//FIGHTING:

	//Function that lowers current health of a unit
	void takeDamage(float amount);

	//
	void attack(Unit* target);

	//Function that returns max health
	float const maxHP() const;

	//Function that returns current health
	float const health() const;

	//Returns Atk
	float const atk() const;

	//Returns AtkSpd
	float const atkSpd() const;

	//Returns range
	float const range_() const;

	//Returns actual speed
	float const speed() const;

	//Returns orginal speed
	float const orginalSpeed_() const;

	//Returns orginal speed
	sf::String const uType_() const;

	//Change movement spped
	void fixSpeed(float value);

	//Change unit position
	void setPosiotion(sf::Vector2f position);

	


	

	
	
};


