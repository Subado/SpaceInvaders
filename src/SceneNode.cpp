#include <SceneNode.hpp>
#include <cassert>
#include <algorithm>

SceneNode::SceneNode()
	: m_parent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->m_parent = this;
	m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &node)
{
	auto found = std::find_if(m_children.begin(), m_children.end(),
			[&node] (Ptr &p) -> bool {return p == nullptr;});

	assert(found != m_children.end());

	Ptr result = std::move(*found);
	result->m_parent = nullptr;
	m_children.erase(found);
	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode *node = this;
			node != nullptr; node = node->m_parent)
	{
		transform *= node->getTransform();
	}

	return transform;
}

Category::Type SceneNode::getCategory() const
{
	return Category::Type::Scene;
}

void SceneNode::onCommand(const Command &command, sf::Time dt)
{
	if (static_cast<unsigned>(command.category) & static_cast<unsigned>(getCategory()))
	{
		command.action(*this, dt);
	}

	for (Ptr &child : m_children)
	{
		child->onCommand(command, dt);
	}
}

void SceneNode::updateCurrent(sf::Time dt)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (Ptr &child : m_children)
	{
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
	for(const Ptr &child : m_children)
	{
		child->draw(target, states);
	}
}

