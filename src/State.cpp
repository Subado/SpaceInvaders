#include <StateStack.hpp>

State::Context::Context(sf::RenderWindow &window, TextureHolder &textures, FontHolder &fonts, Player &player)
	: window(&window),
	textures(&textures),
	fonts(&fonts),
	player(&player)
{
}

State::State(StateStack& stack, Context context)
	: m_stack(&stack),
	m_context(context)
{
}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
	m_stack->pushState(stateID);
}

void State::requestStackPop()
{
	m_stack->popState();
}

void State::requestStackClear()
{
	m_stack->clearStates();
}

State::Context State::getContext() const
{
	return m_context;
}
