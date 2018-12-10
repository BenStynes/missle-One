// author Ben Stynes
//nickname Styner
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
	void fireLaser(sf::Event t_mouseEvent);//mouse click events 
	void update(sf::Time t_deltaTime);
	void render();//renders everything 
	void laserPath();// the lasers path 
	void setupFontAndText(); // sets the font and text
	void setupGround();//sets up the ground 
	void setupBase();//sets up the base
	void setupPowerBar();//sets up the power bar
	void deployAsteroid();//deploys the asteroid 
	void laserExplosion();//creates the laser explosion 
	void asteroidMovement();// the asteroids path and movement 
	void asteroidRespawn();// Respawns the asteroid 
	void animatePowerbar();// animatyes the power bar
	
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_scoreText;//initalizes the score text
	sf::Text m_AltitudeBarText; //initializes the altitude
	sf::Text m_gameOverText;//initalizes the game over text
	bool m_exitGame; // control exiting game
	bool m_mouseClick = false; // see if the mouse clicked 
	bool m_missleFired = false; // see if the missle fired 
	bool m_drawLine = false; // does it draw the line
	bool m_exploded = false; // has it exploded
	bool m_drawExplosion = false;// dpoes itdraw the explosion
	bool m_asteriodSpawned = true; // does it spawn the asteroid 
	bool m_asteriodRespawn = false;//does it respawn the asteroid 
	bool m_animate = false; //does it aniamte the bar

	int   m_asteroidRespawnTimer = 0;// the respwan timers counter
	int   m_asteroidRespawnMaxTimer = rand() % 54 + 11;// the max respawn timer
	int m_scoreValue = 0; // the score value

	float m_distanceBetweenBaseAndClick = 0.0f; // the distance variable
	float m_laserSpeed = 3.0f; //the lasers speed
	float m_sizeOfExplosion = 0.0f;//the explossion size
	float m_explosionMaxSize = 40.0f;// the max explosion size
	float m_powerBarSizeIncrement = 1.0f;//how much teh power bar inccreqases by;
	float m_powerbarMaxSize = 260.0f;//the max power bar size
	float m_asteroidSpeed = 0.9f;//the asteroids speed
	
	sf::VertexArray m_laser{ sf::Lines};//initlaize the laser to a line 
	sf::VertexArray m_asteriod{ sf::Lines };//initlaize the asteroid  to a line
	sf::Vector2f m_laserStart{0,0};//the lasers start point 
	sf::Vector2f m_clickPoint{ 0,0 };//the point the mouse clicks 
	sf::Vector2f m_LaserUnitVector{ 0,0 }; //  teh unit vector for the laser
	sf::Vector2f m_maxAltitude = { 0.0f,0.0f };// the max altitude
	sf::Vector2f m_asteroidUnitVector{ 0,0 };// the asteroids unit vector
	sf::Vector2f m_asteroidStart{ 1.0f *(rand() % 800),0.0f };//the asteroids starting postion
	sf::Vector2f m_asteroidEnd{ 1.0f * (rand() % 800),600.0f };//the asteroids end postion
	sf::Vector2f m_asteroidPos{ 0,0 };//the asteroids curent postion
	sf::Vector2f m_laserPos{ 0,0 };//the lasers current postion
	sf::RectangleShape m_ground;// the ground
	sf::RectangleShape m_base;//the base
	sf::RectangleShape m_powerBar;//the power bar
	sf::CircleShape m_explosion;// the explosion

};

#endif // !GAME

