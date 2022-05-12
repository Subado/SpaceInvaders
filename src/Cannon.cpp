#include <SFML/Graphics/RenderTarget.hpp>
#include <Utility.hpp>
#include <Cannon.hpp>

Cannon::Cannon(const TextureHolder	&textures)
	: m_sprite(textures.get(Textures::ID::Cannon))
{
	centerOrigin(m_sprite);
}

void Cannon::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

Category::Type Cannon::getCategory() const
{
	return Category::Type::Cannon;
}
