// author Ben Stynes

#include "Game.h"
#include <iostream>
#include "MyVector2.h"

/// <summary>
/// default construcor
/// pass parameters fpr sfml window, setup m_exitGame
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupGround(); // load texture
	setupBase();
	setupAsteriod();
	setupPowerBar();
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

	if (m_missleFired == true)
	{
		laserPath();//executes
	}
	if (m_exploded == true)
	{
		laserExplosion();
	}
	if (m_asteriodSpawned == true)
	{
		asteroidMovement();
	}
	if (m_asteriodRespawn == true)

	{
		asteroidRespawn();
	}
	if (m_animate == true)
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

	if (m_asteroidPos.y <= 575)
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
	else
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

	m_scoreText.setFont(m_ArialBlackfont);//
	m_scoreText.setCharacterSize(30);//
	m_scoreText.setPosition(200, 450);//
	m_scoreText.setFillColor(sf::Color::White);//
	m_scoreText.setString("Score: " + std::to_string(m_scoreValue));
	m_AltitudeBarText.setPosition(0, 580);
	m_AltitudeBarText.setCharacterSize(12);
	m_AltitudeBarText.setFont(m_ArialBlackfont);
	m_AltitudeBarText.setFillColor(sf::Color::White);
	m_AltitudeBarText.setString("Altitude:");
	m_gameOverText.setFont(m_ArialBlackfont);
	m_gameOverText.setFillColor(sf::Color::White);
	m_gameOverText.setCharacterSize(59);
	m_gameOverText.setString("Game Over");
	m_gameOverText.setPosition(200, 300);

}

/// <summary>
/// 
/// </summary>
void Game::setupGround()
{
	 m_ground.setSize(sf::Vector2f(800, 50));
	 m_ground.setFillColor(sf::Color::Green);
	 m_ground.setPosition(0,550);
}



/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupBase()
{
	m_base.setSize(sf::Vector2f(50,50));
	m_base.setFillColor(sf::Color(255, 255, 0));
	m_base.setPosition(375, 500);
	m_animate = true;
}



void Game::setupPowerBar()
{
	m_powerBar.setSize(sf::Vector2f(1, 25));
	m_powerBar.setFillColor(sf::Color(255, 0, 0));
	m_powerBar.setPosition(75,580);
}

void Game::setupAsteriod()
{
		
		sf::Vector2f enemyDistanceVec = m_asteroidEnd - m_asteroidStart;
		m_asteroidTempName = vectorUnitVector(enemyDistanceVec);

		m_asteroidPos = m_asteroidStart;

}

void Game::laserExplosion()
{
	m_sizeOfExplosion += 0.5f;
	m_explosion.setRadius(m_sizeOfExplosion);
	m_explosion.setOrigin(m_sizeOfExplosion,m_sizeOfExplosion);
	
	if(m_sizeOfExplosion >=m_explosionMaxSize)
	{
		m_exploded = false;
		m_drawExplosion = false;
		m_animate = true;
	}
	if (vectorLength(sf::Vector2f(m_asteroidPos) - m_explosion.getPosition()) < m_sizeOfExplosion)
	{
		m_asteriodSpawned = false;
		m_asteriodRespawn = true;
		m_asteriod.clear();
		m_exploded = false;
		m_drawExplosion = false;
		m_animate = true;
		m_scoreValue += 5;
		m_scoreText.setString(std::to_string(m_scoreValue));
		
	}

}
void Game::fireLaser(sf::Event t_mouseEvent)
{


	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
	{
		if (m_missleFired == false && m_exploded == false)
		{
			m_sizeOfExplosion = 0.0f;
			m_laser.clear();
			m_missleFired = true;
			m_laserStart = m_base.getPosition();
			m_clickPoint = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
			sf::Vector2f distanceVec = m_clickPoint - m_laserStart;
			m_tempName = vectorUnitVector(distanceVec);
			m_laserPos = m_laserStart;
		}
	
	}

}
///
///
///
///
///
void Game::laserPath()
{

	sf::Vertex lasersStart{ m_laserStart,sf::Color::Red };

	m_laser.append(lasersStart);



	m_laserPos += m_tempName * (m_laserSpeed);

	sf::Vertex lasersPath{ m_laserPos,sf::Color::Red };

	m_laser.append(lasersPath);
		
		m_drawLine = true;
	
	 if (m_laserPos.y <=  m_maxAltitude.y || m_laserPos.y <= m_clickPoint.y)
	{
		 
	
		m_laser.clear();
		m_missleFired = false;
		m_explosion.setPosition(m_laserPos);
		m_exploded = true;
		m_drawExplosion = true;
	}
	
}

void Game::asteroidMovement()
{


	sf::Vertex asteroidStartPoint{ m_asteroidStart ,sf::Color::White };

	m_asteriod.append(asteroidStartPoint);


	m_asteroidPos += m_asteroidTempName * (m_asteroidSpeed);

	sf::Vertex asteroidPath{ m_asteroidPos,sf::Color::White };

	m_asteriod.append(asteroidPath);
	if (m_asteroidPos.x == m_sizeOfExplosion)
	{
		m_asteroidEnd = asteroidPath.position;

	}

}

void Game::asteroidRespawn()
{

		m_asteroidRespawnTimer++;

		if (m_asteroidRespawnTimer == m_asteroidRespawnMaxTimer)
		{
			m_asteroidRespawnTimer = 0;
			m_asteriodSpawned = true;
			m_asteroidStart = { 1.0f * (rand() % 800),0.0f };
			m_asteroidEnd = { 1.0f * (rand() % 800),600.0f };
			m_asteriodRespawn = false;
			setupAsteriod();
		
		}
	

}
void Game::animatePowerbar()
{   
	m_animate = true;
	if (m_powerBarSizeIncrement >= m_powerbarMaxSize)
	{
		m_animate = false;
	}
	if (m_powerBarSizeIncrement < m_powerbarMaxSize)
	{
		
		m_powerBarSizeIncrement++;
		m_maxAltitude.y = 575.0f - (m_powerBarSizeIncrement * 2);
		m_powerBar.setSize(sf::Vector2f{ m_powerBarSizeIncrement,25.0f });
	}


}

