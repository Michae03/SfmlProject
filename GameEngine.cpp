#include "GameEngine.h"
//Private Funcions

void GameEngine::initVariables()
{
    this->window = nullptr;
}

void GameEngine::initWindow()
{
    this->videomode.height = 1080;
    this->videomode.width = 1920;
    this->window = new sf::RenderWindow(this->videomode, "Test_Game");
    this->window->setFramerateLimit(120);
}

void GameEngine::initButtons()
{
    sf::Vector2f buttonSize(75, 75);
    Buttons.push_back(new Button(sf::Vector2f(100, 100), buttonSize, sf::Color::Black)); //Button player 1
    Buttons.push_back(new Button(sf::Vector2f(100, 200), buttonSize, sf::Color::Black)); //Button player 2
    Buttons.push_back(new Button(sf::Vector2f(1500, 100), buttonSize, sf::Color::Black)); //Button enemy 1
    Buttons.push_back(new Button(sf::Vector2f(1500, 200), buttonSize, sf::Color::Black)); //Button enemy 2
    Buttons.push_back(new Button(sf::Vector2f(100, 300), buttonSize, sf::Color::Black)); //Button player 3
    Buttons.push_back(new Button(sf::Vector2f(1500, 300), buttonSize, sf::Color::Black)); //Button enemy 3
}

void GameEngine::consoleLog()
{
   // std::cout << 1 / elapsed.asSeconds() << " FPS " << std::endl;
}


//Constructor, Destructor

GameEngine::GameEngine()
{
    this->initVariables();
    this->initWindow();
    this->initButtons();

    allySpawnPoint = sf::Vector2f(100, this->videomode.height - 200);
    enemySpawnPoint = sf::Vector2f(this->videomode.width - 100, this->videomode.height - 200);
}

GameEngine::~GameEngine()
{
    delete this->window;
    //Deletes all units spawned
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        delete *it;
    }
    //Deletes all buttons spawned
    for (auto it = Buttons.begin(); it != Buttons.end(); ++it)
    {
        delete* it;
    }
}

//Accesors

const bool GameEngine::running() const
{
    return this->window->isOpen();
}

//Functions

void GameEngine::update()
{
    //Resets frame timer
    elapsed = clock.restart();

    //Poll events
    this->pollEvents();

    //Update logic for all units spawned

    //Collision beetwen units. Units have two options, move or attack
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        //Fix speed
        if ((*it) != nullptr)
        {
            if (isColliding(*it))
            {
                if ((*it)->speed() > isCollidingWith(*it)->speed() && (*it)->friendly == isCollidingWith(*it)->friendly)
                {
                    (*it)->fixSpeed(isCollidingWith(*it)->speed());
                }
            }
            else
            {
                if ((*it)->friendly)
                {
                    (*it)->fixSpeed((*it)->orginalSpeed_());
                }
                else
                {
                    (*it)->fixSpeed((*it)->orginalSpeed_() * -1);
                }
            }
        }
        //

        if (*it != nullptr)
        {
            (*it)->update(elapsed);
            if ((*it)->range_() == 0)
            {
                meleeUnitLogic(*it);
            }
            if ((*it)->range_() > 0);
            {
                rangeUnitLogic(*it);
            }
        } 
    }

    //Writes in console
    this->consoleLog();

    //Removes dead units
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr)
        {
            if ((*it)->health() <= 0)
            {
                kill(*it);
            }
        }
    }
    //Updates Buttons logic
    for (auto it = Buttons.begin(); it != Buttons.end(); ++it)
    {
        if (*it != nullptr)
        {
            (*it)->update();
        }
    }
}


void GameEngine::pollEvents()
{
    //Event polling
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }

        if (this->event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                this->window->close();
            }
        }

        //Checks if buttons are clicked
        pollButtons();

       //Checks if units are clicked
        for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
        {
            if (*it != nullptr)
            {
                if ((*it)->isClicked())
                {
                    (*it)->takeDamage(1000);
                }
            }
        }
    }
}

void GameEngine::pollButtons()
{
    float const buttonCDCONST = 0.75;
    
    if (Buttons.at(0)->isClicked() && isSpawnPointFree(allySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("DUMMY", allySpawnPoint, true));
        std::cout << "0 Button clicked" << std::endl;
        buttonCD.restart();
    }
    if (Buttons.at(1)->isClicked() && isSpawnPointFree(allySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("DUMMY_2", allySpawnPoint, true));
        std::cout << "1 Button clicked" << std::endl;
        buttonCD.restart();
    }
    if (Buttons.at(2)->isClicked() && isSpawnPointFree(enemySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("DUMMY", enemySpawnPoint, false));
        std::cout << "2 Button clicked" << std::endl;
        buttonCD.restart();
    }
    if (Buttons.at(3)->isClicked() && isSpawnPointFree(enemySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("DUMMY_2", enemySpawnPoint, false));
        std::cout << "3 Button clicked" << std::endl;
        buttonCD.restart();
    }
    if (Buttons.at(4)->isClicked() && isSpawnPointFree(allySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("Archer_DUMMY", allySpawnPoint, true));
        std::cout << "3 Button clicked" << std::endl;
        buttonCD.restart();
    }
    if (Buttons.at(5)->isClicked() && isSpawnPointFree(enemySpawnPoint) && buttonCD.getElapsedTime().asSeconds() >= buttonCDCONST)
    {
        SpawnedUnits.push_back(new Unit("Archer_DUMMY", enemySpawnPoint, false));
        std::cout << "3 Button clicked" << std::endl;
        buttonCD.restart();
    }

}

void GameEngine::render()
{
    /*
    Renders the game objects
    -clear old frame
    -render objects
    -display frame in window
    */

    //---Clear old frame
    this->window->clear(sf::Color(110, 110, 110, 255));

    //---Draw objects in game
    
    //Draw all unit spawned
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr)
        {
            (*it)->Unit::render(this->window);
        } 
    }

    //Draws all buttons 
    for (auto it = Buttons.begin(); it != Buttons.end(); ++it)
    {
        (*it)->Button::render(this->window);
    }
        
    //---Display frame in window
    this->window->display();
}

void GameEngine::kill(Unit*& unit)
{
    delete unit;
    unit = nullptr;
}

bool GameEngine::isColliding(Unit* unit)
{
    if (unit != nullptr)
    {
        float uLeftBumper = unit->getBumperHitbox().left;
        float uRightBumper = unit->getBumperHitbox().left + unit->getBumperHitbox().width;

        for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
        {
            if (*it != nullptr)
            {
                float iLeftBody = (*it)->getHitbox().left;
                float iRightBody = (*it)->getHitbox().left + (*it)->getHitbox().width;
                //Checks if *it isnt dead unit or same unit as argument
                if ((*it)->healthbar && (*it) != unit)
                {
                    //If unit is friendly (facing right)
                    if (unit->friendly)
                    {
                        if (iLeftBody >= uLeftBumper && iLeftBody <= uRightBumper)
                        {
                            return true;
                        }
                    }
                    //If unit is hostile (facing left)
                    if (!(unit->friendly))
                    {
                        if (iRightBody >= uLeftBumper && iRightBody <= uRightBumper)
                        {
                            return true;
                        }
                    }
                }
            }
          
        }
    }
    return false;
}

Unit* GameEngine::isCollidingWith(Unit* unit)
{
    if (unit != nullptr)
    {
        float uLeftBumper = unit->getBumperHitbox().left;
        float uRightBumper = unit->getBumperHitbox().left + unit->getBumperHitbox().width;

        for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
        {
            if (*it != nullptr)
            {
                float iLeftBody = (*it)->getHitbox().left;
                float iRightBody = (*it)->getHitbox().left + (*it)->getHitbox().width;
                //Checks if *it isnt dead unit or same unit as argument
                if ((*it)->healthbar && (*it) != unit)
                {
                    //If unit is friendly (facing right)
                    if (unit->friendly)
                    {
                        if (iLeftBody >= uLeftBumper && iLeftBody <= uRightBumper)
                        {
                            return *it;
                        }
                    }
                    //If unit is hostile (facing left)
                    if (!(unit->friendly))
                    {
                        if (iRightBody >= uLeftBumper && iRightBody <= uRightBumper)
                        {
                            return *it;
                        }
                    }
                }
            }
          
        }
    }
  
    return nullptr;
}

bool GameEngine::isSpawnPointFree(sf::Vector2f spawnPoint)
{
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr)
        {
            float left = (*it)->getHitbox().left;
            float right = (*it)->getHitbox().left + (*it)->getHitbox().width;
            float xPoint = spawnPoint.x;
            if ((*it)->friendly)
            {
                xPoint += (*it)->getHitbox().width;
            }
            
            if (right >= xPoint && left <= xPoint)
            {
                std::cout << "Spawnpoint is occupied" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool GameEngine::isEnemyInRange(Unit* unit)
{
    float leftB = unit->getRangeHitbox().left;
    float rightB = unit->getRangeHitbox().left + unit->getRangeHitbox().width;
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr && (*it)->friendly != unit->friendly)
        {
            float itLeft = (*it)->getHitbox().left;
            float itRight = (*it)->getHitbox().left + (*it)->getHitbox().width;
            std::cout << "archerBounds: (" << leftB << " ," << rightB << ") ------ it: (" << itLeft << " ," << itRight << ")" << std::endl;
            if ((itLeft >= leftB && itLeft <= rightB) || (itRight >= leftB && itRight <= rightB))
            {
                return true;
            }
        }
    }
    return false;
}

bool GameEngine::isAllyInRange(Unit* unit)
{
    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr && (*it)->friendly == unit->friendly)
        {
            float leftB = unit->getRangeHitbox().left;
            float rightB = unit->getRangeHitbox().left + unit->getRangeHitbox().width;
            float itLeft = (*it)->getHitbox().left;
            float itRight = (*it)->getHitbox().left + (*it)->getHitbox().width;
            if ((itLeft >= leftB && itLeft <= rightB) || (itRight >= leftB && itRight <= rightB))
            {
                return true;
            }
        }
    }
    return false;
}

Unit* GameEngine::closestEnemyInRange(Unit* unit)
{
    std::vector<Unit*> units;

    for (auto it = SpawnedUnits.begin(); it != SpawnedUnits.end(); ++it)
    {
        if (*it != nullptr && (*it)->friendly != unit->friendly)
        {
            float leftB = unit->getRangeHitbox().left;
            float rightB = unit->getRangeHitbox().left + unit->getRangeHitbox().width;
            float itLeft = (*it)->getHitbox().left;
            float itRight = (*it)->getHitbox().left + (*it)->getHitbox().width;
            if ((itLeft >= leftB && itLeft <= rightB) || (itRight >= leftB && itRight <= rightB))
            {
                units.push_back(*it);
            }
        }
    }

    Unit* closestUnit = nullptr;
    float smallestDist = 99999;

    for (auto it = units.begin(); it != units.end(); ++it)
    {
        if (*it != nullptr)
        {
            float dist;
            dist = abs(unit->getBody().getPosition().x - (*it)->getBody().getPosition().x);
            if (dist < smallestDist)
            {
                smallestDist = dist;
                closestUnit = *it;
            }
        }
    }
    return closestUnit;
}

void GameEngine::tryMeeleAttack(Unit* unit)
{
    if (unit != nullptr)
    {
        if (isCollidingWith(unit) != nullptr && isCollidingWith(unit)->friendly != unit->friendly)
        {
            unit->attack(isCollidingWith(unit));
        }
    }
}

void GameEngine::meleeUnitLogic(Unit* unit)
{
    if (!isColliding(unit))
    {
        (unit)->move(elapsed);
    }
    else
    {
        tryMeeleAttack(unit);
    }
}

void GameEngine::rangeUnitLogic(Unit* unit)
{
    if (isColliding(unit) || (!isAllyInRange(unit) && isEnemyInRange(unit)))
    {
       
        if (isEnemyInRange(unit))
        {
            unit->attack(closestEnemyInRange(unit));
        
        }
    }
    else
    {
        unit->move(elapsed);
    }

}




