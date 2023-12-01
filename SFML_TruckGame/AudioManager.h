#pragma once

#include <SFML/Audio.hpp>

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

class AudioManager {
private:
	static std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> audioPtrs;
public:
	static std::shared_ptr<sf::SoundBuffer> Acquire(const std::string& name) {
		const auto i = audioPtrs.find(name);
		if (i != audioPtrs.end()) {
			return i->second;
		}
		else
		{
			auto pSnd = std::make_shared<sf::SoundBuffer>();
			pSnd->loadFromFile(name);
			audioPtrs.insert({ name, pSnd });
			return pSnd;
		}
	}

	static void CollectGarbage() {
		for (auto i = audioPtrs.begin(); i != audioPtrs.end();) {
			if (i->second.unique()) {
				i = audioPtrs.erase(i);
			}
			else
			{
				++i;
			}
		}
	}
};