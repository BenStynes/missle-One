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
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_mouseClick = false;
	bool m_missleFired = false;
	bool m_drawLine = false;
	float m_distanceBetweenBaseAndClick = 0.0f;
	sf::VertexArray m_laser{ sf::Lines };
	sf::VertexArray m_asteriod{ sf::Lines };
	sf::Vector2f m_laserStart{0,0};
	sf::Vector2f m_clickPoint{ 0,0 };
	sf::Vector2f m_tempName{ 0,0 };
	sf::Vector2f m_laserPos{ 0,0 };
	float m_laserSpeed = 0.5f;
	sf::RectangleShape m_ground;
	sf::RectangleShape m_base;
	sf::RectangleShape m_powerBar;

};

#endif // !GAME

