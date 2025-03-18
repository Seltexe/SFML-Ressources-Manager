#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <memory>
#include <string>


template <typename ResourceType>
class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{
		static ResourceManager instance;
		return instance;
	}

	bool load(const std::string& id, const std::string& filename)
	{
		auto resource = std::make_unique<ResourceType>();
		if (!resource->loadFromFile(filename))
			return false;

		m_resources[id] = std::move(resource);
		return true;
	}

	const ResourceType& Get(const std::string& id) const
	{
		if (!exists(id)) {
			throw std::runtime_error("Resource not found: " + id);
		}
		return *m_resources.at(id);
	}

	bool exists(const std::string& id) const 
	{
		return m_resources.find(id) != m_resources.end();
	}

private:
	ResourceManager() = default;
	std::unordered_map<std::string, std::unique_ptr<ResourceType>> m_resources;
};