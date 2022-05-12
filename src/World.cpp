#include <SpriteNode.hpp>
#include <World.hpp>
#include <iostream>

World::World(sf::RenderWindow &window)
	: m_window(window),
	m_worldView(m_window.getDefaultView())
{
	loadTextures();
	buildWorld();
}

void World::update(sf::Time dt)
{
	m_playerCannon->setVelocity(sf::Vector2f(0.f, 0.f));

	while (!m_commandQueue.isEmpty())
	{
		m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
	}

	m_sceneGraph.update(dt);
	adaptPlayerPosition();
}

void World::draw()
{
	m_window.draw(m_sceneGraph);
}

CommandQueue &World::getCommandQueue()
{
	return m_commandQueue;
}

void World::loadTextures()
{
	m_textures.load(Textures::ID::Cannon, "assets/images/cannon.png");
}

void World::buildWorld()
{
	for (size_t i = 0; i < LayerCount; i++)
	{
		std::unique_ptr<SceneNode> layer(new SceneNode());

		m_sceneLayers[i] = layer.get();
		m_sceneGraph.attachChild(std::move(layer));
	}
	sf::Vector2f scale{ 0.2f, 0.2f };
	const float borderDistance = 35.f;

	std::unique_ptr<Cannon> cannon(new Cannon(m_textures));
	cannon->setScale(scale);
	cannon->setPosition(m_window.getSize().x / 2.f, m_window.getSize().y - borderDistance);
	m_playerCannon = cannon.get();
	m_sceneLayers[Foreground]->attachChild(std::move(cannon));
}

void World::adaptPlayerPosition()
{
	const float borderDistance = 35.f;
	const sf::Vector2u windowSize = m_window.getSize();
	sf::Vector2f position = m_playerCannon->getPosition();

	position.x = std::max(position.x, borderDistance);
	position.x = std::min(position.x, windowSize.x - borderDistance);
	position.y = std::max(position.y, borderDistance);
	position.y = std::min(position.y, windowSize.y - borderDistance);
	m_playerCannon->setPosition(position);
}
