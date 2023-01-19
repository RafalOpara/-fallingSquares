#include "Game.h"
//private funcktions

void Game::initializeVariables()
{
	this->window = nullptr;

	//game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 1;
	this->mouseHeld = false;
	this->startTime = clock();
	this->temp = 50;
	this->gameTime = 0;
	
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	

	this->window=new sf::RenderWindow(this->videoMode, "My first game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonsts()
{
	if (this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
	{
		std::cout << "Error::Game::inifont::failed to load font!" << std::endl;
	}
}
/*
void Game::initTime()
{
	
}
*/
void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");
}

void Game::initEnemies()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	//this->enemy.setOutlineColor(sf::Color::Green);
	//this->enemy.setOutlineThickness(1.f);


}


//constuctor / destructors

Game::Game()
{
	this->initializeVariables();
	this->initWindow();
	this->initFonsts();
	this->initText();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}



//accessors
const bool Game::running() const
{

	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//functions

void Game::spawnEnemy()
{
	//spwan randomly and types colors of the enemy 
	//set a random position
	//sets random color
	//adds enemy to the vector

	this->enemy.setPosition(
		static_cast<float>(rand()%static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	//randomize enemy type
	

	if (this->gameTime < 10)
	{
		int type = rand() % 2;
		switch (type)
		{
		case 0:
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;

		case 1:
			this->enemy.setSize(sf::Vector2f(150.f, 150.f));
			this->enemy.setFillColor(sf::Color::Yellow);
			break;
		}
	}
	else if (this->gameTime > 10 && this->gameTime<20)
	{
		int type = rand() % 3;
		switch (type)
		{
		case 0:
			this->enemy.setSize(sf::Vector2f(75.f, 75.f));
			this->enemy.setFillColor(sf::Color::Green);
			break;
		case 1:
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;

		case 2:
			this->enemy.setSize(sf::Vector2f(150.f, 150.f));
			this->enemy.setFillColor(sf::Color::Yellow);
			break;
		}
	}
	else if (this->gameTime > 20 && this->gameTime < 30)
	{
		int type = rand() % 4;
		switch (type)
		{

		case 0:
			this->enemy.setSize(sf::Vector2f(50.f, 50.f));
			this->enemy.setFillColor(sf::Color::Cyan);
			break;
		case 1:
			this->enemy.setSize(sf::Vector2f(75.f, 75.f));
			this->enemy.setFillColor(sf::Color::Green);
			break;
		case 2:
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;

		case 3:
			this->enemy.setSize(sf::Vector2f(150.f, 150.f));
			this->enemy.setFillColor(sf::Color::Yellow);
			break;
		
		}
	}
	else if (this->gameTime > 30)
	{
		if (this->gameTime >= this->temp)
		{
			this->maxEnemies++;
			this->temp = this->temp + 10;
		}

		int type = rand() % 5;
		switch (type)
		{
		case 0:
			this->enemy.setSize(sf::Vector2f(30.f, 30.f));
			this->enemy.setFillColor(sf::Color::Blue);
			break;
		case 1:
			this->enemy.setSize(sf::Vector2f(50.f, 50.f));
			this->enemy.setFillColor(sf::Color::Cyan);
			break;
		case 2:
			this->enemy.setSize(sf::Vector2f(75.f, 75.f));
			this->enemy.setFillColor(sf::Color::Green);
			break;
		case 3:
			this->enemy.setSize(sf::Vector2f(100.f, 100.f));
			this->enemy.setFillColor(sf::Color::Red);
			break;

		case 4:
			this->enemy.setSize(sf::Vector2f(150.f, 150.f));
			this->enemy.setFillColor(sf::Color::Yellow);
			break;

		}
	}
	
	

	//spawn the enemy
	this->enemies.push_back(this->enemy);

}

void Game::poolEvents()
{
	//event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::uptadeMousePositions()
{
	//return void uptade the mouse positions: relative to window (vector2i)

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::uptadeTime()
{
	this->stopTime = clock();
	this->gameTime =  ((double)(this->stopTime - this->startTime)) / CLOCKS_PER_SEC;
	std::cout << gameTime;
}

void Game::uptadeText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << std::endl;
	ss << "Health: " << this->health << std::endl;
	ss << "Time: " << this->gameTime << std::endl;

	this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
	//return void uptade enemy spawn timer and spawn enemies when the total amount of enemies is simillar than the maximum
	//moves enemies


	//updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{


		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//spawn enemy and reset timer 
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimer += 1.f;
	}

	//move the enemies and uptading


	for (int i=0; i<this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 3.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "health: " << this->health << std::endl;
		}
		
	}
	//check if clicked upon

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					
					//gain points
					if(this->enemies[i].getFillColor()==sf::Color::Magenta)
					this->points += 10;
					else if (this->enemies[i].getFillColor() == sf::Color::Blue)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == sf::Color::Red)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == sf::Color::Green)
						this->points += 1;
					
				

					std::cout << "point: " << this->points << std::endl;

					//delete enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
				else
				{
					this->health--;
				}
			}
		}
		
	}
	else
	{
		this->mouseHeld = false;
	}
	
		
}





//funcktions

void Game::uptade()
{
	this->poolEvents();

	if (!this->endGame)
	{

		this->uptadeMousePositions();

		this->uptadeTime();

		this->uptadeText();

		this->updateEnemies();
	}

	//end game condition
	if (this->health <= 0)
	this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//rendering all the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	this->window->clear();

	// draw 
	this->renderEnemies(*this->window);

	this->renderText(*this->window);

	this->window->display();
}


