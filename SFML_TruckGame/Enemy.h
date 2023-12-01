#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "HelperScripts.h"
#include "TextureManager.h"
#include "Animation.h"
#include "Player.h"
#include "Camera.h"
#include "ParticleGenerator.h"
#include "SoundManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy {
private:
	std::shared_ptr<sf::Texture> run_texture;
	std::shared_ptr<sf::Texture> shadow_texture;
	sf::Sprite run_sprite;
	sf::Sprite shadow_sprite;

	Animation run_animation;
public:
	float x;
	float y;
	float spd;
	float hsp;
	float vsp;
	float dir;
	Player* player;
	Camera* camera;
	ParticleGenerator* particle_generator;
	std::vector<Enemy>* enemies;
	int enemies_index;

	Enemy(float _x, float _y, float _spd, float _dir);
	virtual ~Enemy();

	void Kill();
	void update(float dt);
	void draw(sf::RenderWindow* window);
};