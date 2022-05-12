#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>
#include <Category.hpp>
#include <functional>

class SceneNode;

struct Command
{
	Command();

	std::function<void(SceneNode&, sf::Time)> action;
	Category::Type category;
};

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
	return [=] (SceneNode &node, sf::Time dt)
	{
#ifdef DEBUG
		assert(dynamic_cast<GameObject*>(&node) != nullptr);
#endif
		fn(static_cast<GameObject&>(node), dt);
	};
}

#endif // COMMAND_HPP
