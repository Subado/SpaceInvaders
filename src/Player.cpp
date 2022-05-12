#include <Player.hpp>
#include <Cannon.hpp>

struct CannonMover
{
	CannonMover(sf::Vector2f velocity)
		: velocity(velocity)
	{
	}
	
	void operator () (Cannon &cannon, sf::Time dt) const
	{
		cannon.accelerate(velocity);
	}

	sf::Vector2f velocity;
};

Player::Player()
{
	initActions();

	assignKey(Action::MoveLeft, sf::Keyboard::Key::Left);
	assignKey(Action::MoveRight, sf::Keyboard::Key::Right);
}

void Player::handleRealtimeInput(CommandQueue &commands)
{
	for (const auto &pair : m_keyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(m_actionBinding[pair.second]);
		}
	}
}

void Player::handleEvent(const sf::Event &event, CommandQueue &commands)
{
	Command command;

	switch (event.type)
	{
		default:
			break;
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto i = m_keyBinding.begin(); i != m_keyBinding.end(); i++)
	{
		if (i->second == action)
		{
			m_keyBinding.erase(i);
		}
	}

	m_keyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignKey(Action action) const
{
	for (auto pair : m_keyBinding)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Key::Unknown;
}

void Player::initActions()
{
	const float playerSpeed = 500.f;

	Command moveLeft;
	moveLeft.category = Category::Type::Cannon;
	moveLeft.action = derivedAction<Cannon>(CannonMover(sf::Vector2f(-playerSpeed, 0)));
	m_actionBinding[Action::MoveLeft] = moveLeft;

	Command moveRight;
	moveRight.category = Category::Type::Cannon;
	moveRight.action = derivedAction<Cannon>(CannonMover(sf::Vector2f(+playerSpeed, 0)));
	m_actionBinding[Action::MoveRight] = moveRight;
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
		case Action::MoveLeft:
		case Action::MoveRight:
			return true;
		default:
			return false;
	};
}
