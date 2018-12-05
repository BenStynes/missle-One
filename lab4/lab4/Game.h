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
	void processMouseEvents(sf::Event t_mouseEvent);
	void update(sf::Time t_deltaTime);
	void render();
	void setupLaser();
	void setupFontAndText();
	void setupGround();
	void setupBase();
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_mouseClick = false;
	sf::RectangleShape m_ground;
	sf::RectangleShape m_base;
	sf::RectangleShape m_laser;

};

#endif // !GAME

