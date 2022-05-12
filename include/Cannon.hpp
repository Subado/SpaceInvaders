#ifndef CANNON_HPP
#define CANNON_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIDs.hpp>
#include <Entity.hpp>

class Cannon : public Entity
{
public:
	explicit Cannon(const TextureHolder	&textures);

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual Category::Type getCategory() const;

private:
	sf::Sprite m_sprite;
};

#endif // CANNON_HPP
