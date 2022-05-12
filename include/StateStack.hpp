#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include <SFML/System/NonCopyable.hpp>
#include <functional>
#include <State.hpp>
#include <vector>
#include <map>

class StateStack : private sf::NonCopyable
{
public:
	enum class Action
	{
		Push,
		Pop,
		Clear
	};

	explicit StateStack(State::Context context);

	template <typename T>
	void registerState(States::ID stateID);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event &event);

	void pushState(States::ID stateID);
	void popState();
	void clearStates();

	bool isEmpty();

private:
	State::Ptr createState(States::ID stateID);
	void applyPendingChanges();

	struct PendingChange
	{
		explicit PendingChange(Action action, States::ID stateID = States::ID::None);

		Action action;
		States::ID stateID;
	};

	std::vector<State::Ptr> m_stack;
	std::vector<PendingChange> m_pendingList;
	State::Context m_context;
	std::map<States::ID, std::function<State::Ptr()>> m_factories;
};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
	m_factories[stateID] = [this] ()
	{
		return State::Ptr(new T(*this, m_context));
	};
}

#endif // STATE_STACK_HPP
