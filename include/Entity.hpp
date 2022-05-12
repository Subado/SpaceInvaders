#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SceneNode.hpp>

class Entity : public SceneNode
{
public:
	void accelerate(sf::Vector2f velocity);
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;

	virtual void updateCurrent(sf::Time dt);

private:
	sf::Vector2f m_velocity;
};

#endif // ENTITY_HPP
