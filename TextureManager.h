#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

class TextureManager {
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturePtrs;
public:
	static std::shared_ptr<sf::Texture> Acquire(const std::string& name, const sf::IntRect& area = sf::IntRect()) {
		const auto i = texturePtrs.find(name);
		if (i != texturePtrs.end()) {
			return i->second;
		}
		else
		{
			auto pTex = std::make_shared<sf::Texture>();
			pTex->loadFromFile(name, area);
			texturePtrs.insert({ name, pTex });
			return pTex;
		}
	}

	static void CollectGarbage() {
		for (auto i = texturePtrs.begin(); i != texturePtrs.end();) {
			if (i->second.unique()) {
				i = texturePtrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
};