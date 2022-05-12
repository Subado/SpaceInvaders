#ifndef APP_HPP
#define APP_HPP

#include <ResourceHolder.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceIDs.hpp>
#include <StateStack.hpp>

class App
{
public:
	App();
	void run();

private:
	void handleInput();
	void update(sf::Time elapsedTime);
	void render();

	void registerStates();

	static const sf::Time timePerFrame;

	sf::RenderWindow m_window;
	TextureHolder m_textures;
	FontHolder m_fonts;
	Player m_player;

	StateStack m_stateStack;
};

#endif // APP_HPP
