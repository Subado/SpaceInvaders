#ifndef RESOURCE_HOLDER_HPP
#define RESOURCE_HOLDER_HPP

#include <SFML/Graphics/Texture.hpp>
#include <stdexcept>
#include <cassert>
#include <memory>
#include <map>

template <typename Resource, typename Identifier>
class ResourceHolder
{
	std::map<Identifier, std::unique_ptr<Resource>> m_resourceMap;

	void insertResource(Identifier id, std::unique_ptr<Resource> resource);

public:
	void load(Identifier id, const std::string& filename);
	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter &secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
};

#include <ResourceHolder.inl>

#endif // RESOURCE_HOLDER_HPP
