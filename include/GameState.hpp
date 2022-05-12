#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <Player.hpp>
#include <World.hpp>
#include <State.hpp>

class GameState : public State
{
public:
	GameState(StateStack& stack, State::Context context);

	virtual void draw();
	virtual bool update(sf::Time elapsedTime);
	virtual bool handleEvent(const sf::Event &event);

private:
	World m_world;
	Player &m_player;
};

#endif // GAME_STATE_HPP
