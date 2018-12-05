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
	setupLaser();
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
		processMouseEvents(event); // keep code tidy
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
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear();
	m_window.draw(m_base);
	m_window.draw(m_ground);
	m_window.draw(m_laser);
	m_window.display();
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
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupGround()
{
	 m_ground.setSize(sf::Vector2f(800, 50));
	 m_ground.setFillColor(sf::Color(0,100,0));
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
}

void Game::setupLaser()
{
	m_laser.setSize(sf::Vector2f(0,0));
	m_laser.setFillColor(sf::Color(255, 0, 0));
	m_laser.setPosition(m_base.getPosition().x, m_base.getPosition().y);
}

//void Game::processMouseEvents(sf::Event t_mouseEvent)
//{
//	sf::Vertex lineStart{}; // start point of line
//	sf::Vertex lineEnd{}; // end point of line
//	sf::Vector2f mouseClick{}; // location of mouse click 
//	
//
//
//
//	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
//	{
//		lineStart = m_base.getPosition();
//		mouseClick = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x),static_cast<float>(t_mouseEvent.mouseButton.y) };
//	}
//
//}