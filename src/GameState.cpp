#include <StateIDs.hpp>
#include <CommandQueue.hpp>
#include <GameState.hpp>

GameState::GameState(StateStack &stack, State::Context context)
	: State(stack, context),
	m_world(*context.window),
	m_player(*context.player)
{
}

void GameState::draw()
{
	m_world.draw();
}

bool GameState::update(sf::Time elapsedTime)
{
	m_world.update(elapsedTime);

	CommandQueue &commands = m_world.getCommandQueue();
	m_player.handleRealtimeInput(commands);

	return true;
}


bool GameState::handleEvent(const sf::Event &event)
{
	CommandQueue &commands = m_world.getCommandQueue();
	m_player.handleEvent(event, commands);
	
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		// requestStackPush(States::ID::Pause);
	}

	return true;
}
