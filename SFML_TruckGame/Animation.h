#pragma once

#include <iostream>

#include "TextureManager.h"

#include <SFML/Graphics.hpp>

class Animation {
private:
	static constexpr int nFrames = 4;
	static constexpr float image_speed = 0.1f;
	std::shared_ptr<sf::Texture> texture;
	sf::IntRect frames[nFrames];
	int image_index = 0;
	float time = 0.0f;

	void Advance() {
		if (++image_index >= nFrames) {
			image_index = 0;
		}
	}
public:
	Animation(const std::string& name, int _x, int _y, int _w, int _h) {
		texture = TextureManager::Acquire(name);
		for (int i = 0; i < nFrames; i++) {
			frames[i] = { _x + i * _w, _y,_w,_h };
		}
	}

	void ApplyToSprite(sf::Sprite& s) const{
		s.setTexture(*texture);
		s.setTextureRect(frames[image_index]);
	}

	void update(float dt) {
		time += dt;
		while (time >= image_speed) {
			time -= image_speed;
			Advance();
		}
	}
};