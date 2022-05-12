#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window/Event.hpp>
#include <CommandQueue.hpp>
#include <map>

class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		Fire,
		ActionCount
	};

	Player();

	void handleRealtimeInput(CommandQueue &commands);
	void handleEvent(const sf::Event &event, CommandQueue &commands);

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignKey(Action action) const;

private:
	void initActions();

	static bool isRealtimeAction(Action action);

	std::map<sf::Keyboard::Key, Action> m_keyBinding;
	std::map<Action, Command> m_actionBinding;
};

#endif // PLAYER_HPP
