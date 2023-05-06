#pragma once
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Unit.h"
#include "Button.h"
#include <vector>

// Game Engine


class GameEngine
{
private:
	//Dynamic window
	sf::RenderWindow* window;	
	//Window preferences
	sf::VideoMode videomode;		
	//Event handling
	sf::Event event;				
	//Time measuring
	sf::Clock clock; 
	sf::Time elapsed;
	sf::Clock buttonCD;
	//Spawn points for units
	sf::Vector2f allySpawnPoint;
	sf::Vector2f enemySpawnPoint;

	//Buttons
	std::vector<Button*> Buttons;
	
	//Units
	std::vector<Unit*> SpawnedUnits;

	//Private Funcions
	
	//Initialize Game variables
	void initVariables();	
	//Initialize Window
	void initWindow();	
	//Initialize Buttons
	void initButtons();
	//Console Log
	void consoleLog();

public:

	//Constructor
	GameEngine();

	//Destructor
	virtual ~GameEngine();

	//Accesors

	//Check if the game is running
	const bool running() const; 

	//
	
	//Functions

	//Poll events
	void pollEvents();	

	//Check if any button is clicked
	void pollButtons();

	//Update game logic
	void update();		

	//Renders the game objects
	void render();				

	//kills a unit
	void kill(Unit*& unit);

	//Returns true if there is collision and unit it is colliding with
	bool isColliding(Unit* unit);

	//Returns what Unit is colliding with
	Unit* isCollidingWith(Unit* unit);

	//Checks if spawnpoint is free
	bool isSpawnPointFree(sf::Vector2f spawnPoint);

	//Returns true if there is enemy in range
	bool isEnemyInRange(Unit* unit);

	//Returns true if there is ally in range
	bool isAllyInRange(Unit* unit);

	//Returns enemy unit that is closest in range
	Unit* closestEnemyInRange(Unit* unit);
	

	//FIGHTING:
	//Unit attempt attack on another unit that is colliding with
	void tryAttack(Unit* unit);
};

