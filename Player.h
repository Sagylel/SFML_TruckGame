#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "HelperScripts.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "ParticleGenerator.h"

class Player {
private:
	std::shared_ptr<sf::Texture> texture[50];
	std::shared_ptr<sf::Texture> shadow_texture;
	std::shared_ptr<sf::Texture> mask_texture;

	//Audio
	std::shared_ptr<sf::SoundBuffer> truck_sound_buffer;
	sf::Sound truck_sound;
public:
	float x;
	float y;
	float spd;
	float hsp;
	float vsp;
	float start_fric;
	float end_fric;
	float angle;

	bool game_over = false;
	bool started = false;

	float stop_t = 0;
	float stop_tmax = 60 * 1;

	ParticleGenerator* particle_generator;

	float tire_particle_t = 0;
	float tire_particle_tmax = 1;

	sf::Sprite sprite[50];
	sf::Sprite shadow_sprite;
	sf::Sprite mask_sprite;

	Player(float _x, float _y);
	void update(float dt);
	void draw(sf::RenderWindow *window);
};