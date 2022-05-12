#include <ResourceHolder.hpp>
#include <MenuState.hpp>
#include <Utility.hpp>

MenuState::MenuState(StateStack& stack, Context context)
	: State{stack, context},
	m_optionIndex{},
	m_options{}
{
	// m_backgroundSprite.setTexture(context.textures->get(Textures::ID::TitleScreen));

	sf::Vector2f viewSize{ context.window->getDefaultView().getSize() };
	sf::Font &font{ context.fonts->get(Fonts::ID::Main) };

	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin<sf::Text>(playOption);
	playOption.setPosition(viewSize / 2.f);
	m_options.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin<sf::Text>(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	m_options.push_back(exitOption);

	size_t size{m_options.size()};
	sf::Text *ptr{&m_options[0]};

	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow &window = *getContext().window;

	// window.draw(m_backgroundSprite);

	for (sf::Text &option : m_options)
	{
		window.draw(option);
	}
}

bool MenuState::update(sf::Time dt)
{
	updateOptionText();

	return true;
}

bool MenuState::handleEvent(const sf::Event &event)
{
	switch (event.type)
	{
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
				case sf::Keyboard::Enter:
					switch (static_cast<MenuState::OptionNames>(m_optionIndex))
					{
						case OptionNames::Play:
							requestStackPop();
							requestStackPush(States::ID::Game);
							break;

						case OptionNames::Exit:
							requestStackPop();
							break;
					}
					break;

				case sf::Keyboard::Up:
					if (m_optionIndex > 0)
					{
						m_optionIndex--;
					}
					else
					{
						m_optionIndex = m_options.size() - 1;
					}

					updateOptionText();
					break;

				case sf::Keyboard::Down:
					if (m_optionIndex < m_options.size() - 1)
					{
						m_optionIndex++;
					}
					else
					{
						m_optionIndex = 0;
					}

					updateOptionText();
					break;

				default:
					break;
			}
			break;

		default:
			break;
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (m_options.empty())
	{
		return;
	}

	for (sf::Text &text : m_options)
	{
		text.setOutlineColor(sf::Color(236, 239, 244));
		text.setFillColor(sf::Color(236, 239, 244));
	}

	m_options[m_optionIndex].setOutlineColor(sf::Color(163, 190, 140));
	m_options[m_optionIndex].setFillColor(sf::Color(163, 190, 140));
}
