#include <TitleState.hpp>
#include <MenuState.hpp>
#include <GameState.hpp>
#include <StateIDs.hpp>
#include <iostream>
#include <App.hpp>

const sf::Time App::timePerFrame = sf::seconds(1.f/60);

App::App()
	: m_window(sf::VideoMode(700, 700), "Chess on C++"),
	m_stateStack(State::Context(m_window, m_textures, m_fonts, m_player))
{
	m_window.setFramerateLimit(60);

	m_fonts.load(Fonts::ID::Main, "assets/fonts/Hack.ttf");
	// m_textures.load(Textures::ID::TitleScreen, "assets/images/title-screen.png");

	registerStates();
	m_stateStack.pushState(States::ID::Game);
}

void App::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	while (m_window.isOpen())
	{
		for (timeSinceLastUpdate += clock.restart(); timeSinceLastUpdate > timePerFrame; timeSinceLastUpdate -= timePerFrame)
		{
			handleInput();
			update(timePerFrame);

			if (m_stateStack.isEmpty())
			{
				m_window.close();
			}
		}

		render();
	}
}

void App::handleInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		m_stateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

void App::update(sf::Time elapsedTime)
{
	m_stateStack.update(elapsedTime);
}

void App::render()
{
	m_window.clear();

	m_stateStack.draw();
	m_window.setView(m_window.getDefaultView());

	m_window.display();
}

void App::registerStates()
{
	// m_stateStack.registerState<MenuState>(States::ID::Menu);
	m_stateStack.registerState<GameState>(States::ID::Game);
}
