// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void processEvents();
	void fireLaser(sf::Event t_mouseEvent);
	void update(sf::Time t_deltaTime);
	void render();
	void laserPath();
	void setupFontAndText();
	void setupGround();
	void setupBase();
	void setupPowerBar();
	void setupAsteriod();
	void laserExplosion();
	void asteroidMovement();
	void asteroidRespawn();
	void animatePowerbar();
	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_scoreText;
	sf::Text m_AltitudeBarText; 
	sf::Text m_gameOverText;
	bool m_exitGame; // control exiting game
	bool m_mouseClick = false;
	bool m_missleFired = false;
	bool m_drawLine = false;
	bool m_exploded = false;
	bool m_drawExplosion = false;
	bool m_asteriodSpawned = true;
	bool m_asteriodRespawn = false;
	bool m_animate = false;

	int   m_asteroidRespawnTimer = 0;
	int   m_asteroidRespawnMaxTimer = rand() % 54 + 11;
	int m_scoreValue = 0;

	float m_distanceBetweenBaseAndClick = 0.0f;
	float m_laserSpeed = 3.0f;
	float m_sizeOfExplosion = 0.0f;
	float m_explosionMaxSize = 40.0f;
	float m_powerBarSizeIncrement = 1.0f;
	float m_powerbarMaxSize = 260.0f;
	float m_asteroidSpeed = 0.9f;
	
	sf::VertexArray m_laser{ sf::Lines};
	sf::VertexArray m_asteriod{ sf::Lines };
	sf::Vector2f m_laserStart{0,0};
	sf::Vector2f m_clickPoint{ 0,0 };
	sf::Vector2f m_tempName{ 0,0 };
	sf::Vector2f m_maxAltitude = { 0.0f,0.0f };
	sf::Vector2f m_asteroidTempName{ 0,0 };
	sf::Vector2f m_asteroidStart{ 1.0f *(rand() % 800),0.0f };
	sf::Vector2f m_asteroidEnd{ 1.0f * (rand() % 800),600.0f };
	sf::Vector2f m_asteroidPos{ 0,0 };
	sf::Vector2f m_laserPos{ 0,0 };
	sf::RectangleShape m_ground;
	sf::RectangleShape m_base;
	sf::RectangleShape m_powerBar;
	sf::CircleShape m_explosion;

};

#endif // !GAME

