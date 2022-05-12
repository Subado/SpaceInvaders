#include <StateStack.hpp>
#include <cassert>

StateStack::StateStack(State::Context context)
	: m_context(context)
{
}

void StateStack::update(sf::Time dt)
{
	for (auto i = m_stack.rbegin(); i != m_stack.rend(); ++i)
	{
		if (!(*i)->update(dt))
		{
			return;
		}
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (State::Ptr &state : m_stack)
	{
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event &event)
{
	for (auto i = m_stack.rbegin(); i != m_stack.rend(); ++i)
	{
		if (!(*i)->handleEvent(event))
		{
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::pushState(States::ID stateID)
{
	m_pendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	m_pendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	m_pendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty()
{
	return m_stack.empty();
}

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = m_factories.find(stateID);
#ifdef DEBUG
	assert(found != m_factories.end());
#endif

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(PendingChange &change : m_pendingList)
	{
		switch (change.action)
		{
			case Action::Push:
				m_stack.push_back(createState(change.stateID));
				break;

			case Action::Pop:
				m_stack.pop_back();
				break;

			case Action::Clear:
				m_stack.clear();
				break;
		}
	}

	m_pendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, States::ID stateID)
	: action(action),
	stateID(stateID)
{
}
