// author Ben Stynes

#include "Game.h"
#include <iostream>
#include "MyVector2.h"

/// <summary>
/// default construcor
/// pass parameters fpr sfml window, setup m_exitGame
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Rock Exploder 9000" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupGround(); // load texture
	setupBase();// sets up the base 
	deployAsteroid();// sets up the asteroids 
	setupPowerBar();//sets up the power bar
}

/// <summary>
/// default destructor for game, nothing to release
/// </summary>
Game::~Game()
{
}


/// <summary>
/// game loop running at 60fps
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
		
	}
	if (sf::Event::MouseButtonPressed == event.type)
	{
		fireLaser(event); // keep code tidy
		m_animate = false;//sets the power bar to stop moving 
		m_powerBarSizeIncrement = 1.0f;//sets the increment back to 1
	}

}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{

	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_missleFired == true)//executes the lasers path if the missle is fired
	{
		laserPath();
	}
	if (m_exploded == true) // if its exploded it triggers the function 
	{
		laserExplosion();
	}
	if (m_asteriodSpawned == true)//if the asteroid is spawned it moves 
	{
		asteroidMovement();
	}
	if (m_asteriodRespawn == true)//if the asteroid respawns it executes the function
	{
		asteroidRespawn();
	}
	if (m_animate == true) //if its animateing it moves the power bar 
	{
		animatePowerbar();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear();

	if (m_asteroidPos.y <= 575)// if the asteroid is not  touching the middle of the  ground it draws everything 
	{
		m_window.draw(m_base);
		m_window.draw(m_ground);
		if (m_drawLine == true)
		{
			m_window.draw(m_laser);
		}
		if (m_drawExplosion == true)
		{
			m_window.draw(m_explosion);
		}
		m_window.draw(m_asteriod);
		m_window.draw(m_powerBar);
		m_window.draw(m_AltitudeBarText);
		m_window.display();
			
	}
	else //otherwise it displays the score and game over text
	{
		m_window.draw(m_scoreText);
		m_window.draw(m_gameOverText);
		m_window.display();
	}

	
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}

	m_scoreText.setFont(m_ArialBlackfont);//set up the font 
	m_scoreText.setCharacterSize(30);//set up the size
	m_scoreText.setPosition(200, 450);//set the position
	m_scoreText.setFillColor(sf::Color::White);//set the colour 
	m_scoreText.setString("Score: " + std::to_string(m_scoreValue));//set the text 
	m_AltitudeBarText.setPosition(0, 580);//set the position
	m_AltitudeBarText.setCharacterSize(12);//set up the size
	m_AltitudeBarText.setFont(m_ArialBlackfont);//set up the font
	m_AltitudeBarText.setFillColor(sf::Color::White);//set the colour 
	m_AltitudeBarText.setString("Altitude:");//set the text
	m_gameOverText.setFont(m_ArialBlackfont);//set up the font
	m_gameOverText.setFillColor(sf::Color::White);//set the colour 
	m_gameOverText.setCharacterSize(59);//set up the size
	m_gameOverText.setString("Game Over");//set the text
	m_gameOverText.setPosition(200, 300);//set the position

}

/// <summary>
/// Sets up the ground, its postion and color abd size
/// </summary>
void Game::setupGround()
{
	 m_ground.setSize(sf::Vector2f(800, 50));
	 m_ground.setFillColor(sf::Color::Green);
	 m_ground.setPosition(0,550);
}



/// <summary>
/// sets up the base size ,color and postion
/// </summary>
void Game::setupBase()
{
	m_base.setSize(sf::Vector2f(50,50));
	m_base.setFillColor(sf::Color(255, 255, 0));
	m_base.setPosition(375, 500);
	
}


/// <summary>
///  sets up the powerbar size ,color and postion and sets animate to true
/// </summary>
void Game::setupPowerBar()
{
	m_powerBar.setSize(sf::Vector2f(1, 25));
	m_powerBar.setFillColor(sf::Color(255, 0, 0));
	m_powerBar.setPosition(75,580);
	m_animate = true;
}
/// <summary>
///deploys the asteroid
/// </summary>
void Game::deployAsteroid()
{
		
	sf::Vector2f asteroidDistanceVec = m_asteroidEnd - m_asteroidStart;//sets the ditsance vector of the enemy 
		m_asteroidUnitVector = vectorUnitVector(asteroidDistanceVec);//sets the asteroid unit vector 

		m_asteroidPos = m_asteroidStart;//sets the asteroid postion to its starting postion 
}
/// <summary>
/// the lasers explosion the setup for it i.e the color and postion and how much it  and the collision detection
/// </summary>
void Game::laserExplosion()
{
	m_sizeOfExplosion += 0.5f;
	m_explosion.setRadius(m_sizeOfExplosion);
	m_explosion.setOrigin(m_sizeOfExplosion,m_sizeOfExplosion);
	m_explosion.setFillColor(sf::Color::Yellow);
	
	if(m_sizeOfExplosion >=m_explosionMaxSize) //if it rteaches its max size it stops drawing it and re animates the power bar
	{
		m_exploded = false;
		m_drawExplosion = false;
		m_animate = true;
	}
	if (vectorLength(sf::Vector2f(m_asteroidPos) - m_explosion.getPosition()) < m_sizeOfExplosion) // ifthe metor touches with the the explosion
	{
		m_asteriodSpawned = false;//stops spawing the asteroid 
		m_asteriodRespawn = true;//starts respawnining it
		m_asteriod.clear(); //clears the asteroid line
		m_exploded = false;//stops expoloding 
		m_drawExplosion = false;//stops drawing the explosion
		m_animate = true;//animates the bar again
		m_scoreValue += 5;//increases score by 5
		m_scoreText.setString("Score: " + std::to_string(m_scoreValue));//sets the score string to that;
		
	}

}
/// <summary>
/// if theres a left click it fires the laser if isnt firing   and not exploding 
/// </summary>
/// <param name="t_mouseEvent"></param>
void Game::fireLaser(sf::Event t_mouseEvent)
{


	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
	{
		if (m_missleFired == false && m_exploded == false)
		{
			m_sizeOfExplosion = 0.0f;//resets the explosion size
			m_laser.clear();//clears the laser if any remain
			m_missleFired = true; //sets it so it is firing 
			m_laserStart = m_base.getPosition();//sets the start postion to the bases start 
			m_clickPoint = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
			//takes in mouse clcik postion
			sf::Vector2f distanceVec = m_clickPoint - m_laserStart; //distance of the line 
			m_LaserUnitVector = vectorUnitVector(distanceVec);// the lasers unit vector
			m_laserPos = m_laserStart;//sets the lasrers postion to the start 
		}
	
	}

}
/// <summary>
/// the lasers path 
/// </summary>
void Game::laserPath()
{

	sf::Vertex lasersStart{ m_laserStart,sf::Color::Red }; //makes sure its red and is set to the start 

	m_laser.append(lasersStart);//appensds the starting



	m_laserPos += m_LaserUnitVector * (m_laserSpeed); // calculates the lasers postion

	sf::Vertex lasersPath{ m_laserPos,sf::Color::Red };// makes sure its path is set to the postion and that the color is red

	m_laser.append(lasersPath);//appends the path 
		
		m_drawLine = true;//draws the linb
	
	 if (m_laserPos.y <=  m_maxAltitude.y || m_laserPos.y <= m_clickPoint.y)// if it hits  the max altitude orthe click point
	{
		 
	
		m_laser.clear();//clears the laser
		m_missleFired = false;//MISSLE NO LONER FIRED
		m_explosion.setPosition(m_laserPos);//explosion start = laser postion
		m_exploded = true;//missle exploded
		m_drawExplosion = true;//draws the explosion
	}
	
}
/// <summary>
/// the asteroids path and movement 
/// </summary>
void Game::asteroidMovement()
{


	sf::Vertex asteroidStartPoint{ m_asteroidStart ,sf::Color::White }; //sets it ot the start 

	m_asteriod.append(asteroidStartPoint);//apeneds it


	m_asteroidPos += m_asteroidUnitVector * (m_asteroidSpeed);//calcuates the position

	sf::Vertex asteroidPath{ m_asteroidPos,sf::Color::White };//sets the path 

	m_asteriod.append(asteroidPath); //appends the path
	

}
/// <summary>
/// Respawns the asteroid 
/// </summary>
void Game::asteroidRespawn()
{
	   
		m_asteroidRespawnTimer++;//increments the timer

		if (m_asteroidRespawnTimer == m_asteroidRespawnMaxTimer) //if it reaches the respawn cooldown
		{
			m_asteroidRespawnTimer = 0;//sets the timer to 0
			m_asteriodSpawned = true;//spawns an asteroid
			m_asteroidStart = { 1.0f * (rand() % 800),0.0f };//sets the start to a random postion  
			m_asteroidEnd = { 1.0f * (rand() % 800),600.0f };//sets the end to a random postion  
			m_asteriodRespawn = false;//stops respawning it
			deployAsteroid();//executes its deployment 
		
		}
	

}
/// <summary>
/// animatyes the power bar
/// </summary>
void Game::animatePowerbar()
{   //sets aniamte to truw when called
	m_animate = true;
	if (m_powerBarSizeIncrement >= m_powerbarMaxSize)//if its greatrer than or = to the max size it stops animating it
	{
		m_animate = false;
	}
	if (m_powerBarSizeIncrement < m_powerbarMaxSize)
	{
		
		m_powerBarSizeIncrement++;//incteemnets it
		m_maxAltitude.y = 575.0f - (m_powerBarSizeIncrement * 2);//calculates the max altitude
		m_powerBar.setSize(sf::Vector2f{ m_powerBarSizeIncrement,25.0f });//sets the size of the power bar to be the incremented value
	}


}

