#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SceneNode.hpp>

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture &texture);
	SpriteNode(const sf::Texture &texture, const sf::IntRect &rect);

	void setPosition(const sf::Vector2f &position);

private:
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Sprite m_sprite;
};

#endif // SPRITE_NODE_HPP
