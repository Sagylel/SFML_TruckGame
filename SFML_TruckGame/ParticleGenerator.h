#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#include "TextureManager.h"
#include "HelperScripts.h"

enum ParticleType {
	blood_floor,
	blood_splash,
	truck_smoke,
	truck_tire,
};

class Particle {
private:
	
public:
	float x;
	float y;
	float alpha;
	float life_max;
	float life;
	float angle;
	std::shared_ptr<sf::Texture> texture;
	sf::Sprite sprite;
	ParticleType type;

	Particle(float _x, float _y, ParticleType _type, float _life, float _angle);
};

class ParticleGenerator {
private:
	
public:
	std::vector<Particle> particles;
	void Emit(float _x, float _y, ParticleType _type, float _life, float _angle);

	void update();
	void draw(sf::RenderWindow* window);

	ParticleGenerator();
};