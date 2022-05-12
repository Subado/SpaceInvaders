#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <StateStack.hpp>

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event &event);

	void updateOptionText();


private:
	enum class OptionNames
	{
		Play,
		Exit
	};

	sf::Sprite m_backgroundSprite;

	std::vector<sf::Text> m_options;
	size_t m_optionIndex;
};
