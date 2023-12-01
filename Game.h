#pragma once

#include <iostream>
#include <ctime>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <cstdlib>

#include "Player.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "ParticleGenerator.h"
#include "Camera.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine.
	Wrapper class
*/

class Game
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;

	//Game Logic
	int enemy_spawn_tmax = 15;
	int enemy_spawn_t = 0;

	//Textures and Sprites
	std::shared_ptr<sf::Texture> background_texture;
	sf::Sprite background_sprite;

	//Private functions
	void initVariables();
	void initWindow();
public:
	//Constructors and Destructors
	Game();
	virtual ~Game();

	//Game Objects
	std::vector<Enemy> enemies;

	//Variables
	float distance_traveled;
	float enemy_speeds;

	//Fonts
	sf::Font font_0;

	//Texts
	sf::Text distance_traveled_text;
	sf::Text game_over_text;

	//Delta Time
	float deltaTime;

	//Accessors
	const bool getWindowIsOpen() const;

	//Functions
	void ResetGame();
	void pollEvents();
	void updateMousePositions();
	void update();
	void render();
};