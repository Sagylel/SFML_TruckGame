#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<sf::Texture>> TextureManager::texturePtrs;
std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> AudioManager::audioPtrs;

Player player(160,120);
Camera camera(0, 0, 480, 270);
ParticleGenerator particle_generator;

//Timepoint for delta time measurement
auto tp = std::chrono::steady_clock::now();

void Game::initVariables()
{
	this->window = nullptr;

	//Background Sprite
	background_texture = TextureManager::Acquire("Resources/Sprites/sBackground.png");
	background_sprite.setTexture(*background_texture);

	distance_traveled = 0;

	enemy_speeds = 2;

	player.particle_generator = &particle_generator;

	camera.target_player = &player;

	if (!font_0.loadFromFile("Resources/Fonts/Pixellari.ttf")) {
		std::cout << "Error loading font!" << "\n";
	}

	distance_traveled_text.setFont(font_0);
	distance_traveled_text.setCharacterSize(24);
	distance_traveled_text.setFillColor(sf::Color::White);

	game_over_text.setFont(font_0);
	game_over_text.setCharacterSize(24);
	game_over_text.setFillColor(sf::Color::Red);
}


void Game::initWindow()
{
	this->videoMode.width = 1920;
	this->videoMode.height = 1080;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);

	this->window->setView(camera.view);
}

//Constructors and Destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
}

Game::~Game() {
	delete this->window;
}

//Accessors
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

//Functions
void Game::ResetGame() {
	distance_traveled = 0;
	enemy_speeds = 2;

	player.game_over = false;
	player.stop_t = 0;
	player.started = false;
	player.x = 0;
	player.y = 0;
	player.hsp = 0;
	player.vsp = 0;

	camera.zoom = 1;
	camera.x = player.x - (camera.w / 2);
	camera.y = player.y - (camera.h / 2);

	enemies.erase(enemies.begin(),enemies.end());
}

void Game::pollEvents() {
	//Get Delta Time
	{
		const auto new_tp = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration<float>(new_tp - tp).count();
		tp = new_tp;
	}

	//Event polling
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
			case sf::Event::Closed:
				this->window->close();
			break;

			case sf::Event::KeyPressed:
				//Close game
				if (this->ev.key.code == sf::Keyboard::Escape) {
					this->window->close();
				}

				//Restart game after game over
				if (this->ev.key.code == sf::Keyboard::Escape || this->ev.key.code == sf::Keyboard::Space) {
					if (player.game_over) {
						ResetGame();
					}
				}
			break;
		}
	}
}

void Game::updateMousePositions() {
	this->mousePosWindow = sf::Mouse::getPosition();
	this->mousePosScreen = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	//Game Logic

	//Camera shake when driving
	camera.shake_amnt += sqrt((player.hsp * player.hsp) + (player.vsp * player.vsp)) * .5f;

	//Enemy spawning
	if (--enemy_spawn_t <= 0) {
		//spawn enemy
		//Select random position
		int win_dir = rand() % 4;
		float sx = 0;
		float sy = 0;
		float outside_offset = 32;
		float enemy_dir = 0;
		switch (win_dir) {
		case 0:
			//top of camera
			sx = camera.x + (rand() % (int)camera.w);
			sy = camera.y - outside_offset;
			enemy_dir = HelperScripts::AngleBetween(sx, sy, player.x, player.y);
			break;
		case 1:
			//right of camera
			sx = camera.x + camera.w + outside_offset;
			sy = camera.y + (rand() % (int)camera.h);
			enemy_dir = HelperScripts::AngleBetween(sx, sy, player.x, player.y) + 180;
			break;
		case 2:
			//bottom of camera
			sx = camera.x + (rand() % (int)camera.w);
			sy = camera.y + camera.h + outside_offset;
			enemy_dir = HelperScripts::AngleBetween(sx, sy, player.x, player.y);
			break;
		case 3:
			//left of camera
			sx = camera.x - outside_offset;
			sy = camera.y + (rand() % (int)camera.h);
			enemy_dir = HelperScripts::AngleBetween(sx, sy, player.x, player.y);
			break;
		}

		enemy_speeds += .005f;

		Enemy enemy(sx, sy, enemy_speeds, enemy_dir);
		enemy.player = &player;
		enemy.camera = &camera;
		enemy.particle_generator = &particle_generator;
		enemy.enemies = &enemies;
		enemy.enemies_index = this->enemies.size();

		this->enemies.push_back(enemy);
		enemy_spawn_t = enemy_spawn_tmax + ((rand() % enemy_spawn_tmax / 2) - enemy_spawn_tmax / 4);
	}

	//player update
	player.update(deltaTime);
	//camera zoom stop time
	camera.zoom = (player.stop_t / player.stop_tmax) * .5;
	//distance traveled
	distance_traveled += sqrt((player.hsp * player.hsp) + (player.vsp * player.vsp)) * 4;

	//enemy update
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i].update(deltaTime);
	}

	//Particle update
	particle_generator.update();

	//camera update
	camera.update(deltaTime);
	this->window->setView(camera.view);

	if(player.game_over){
		camera.zoom = 0;
		//camera update
		camera.update(deltaTime);
		this->window->setView(camera.view);
	}

	TextureManager::CollectGarbage();
	AudioManager::CollectGarbage();
}

void Game::render()
{
	/*
		
		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects.
	*/
	this->window->clear(sf::Color(50, 50, 50, 255));

	//Draw Tiled Background
	background_sprite.setPosition(HelperScripts::SnapToGrid(camera.x, 128), HelperScripts::SnapToGrid(camera.y, 128));
	this->window->draw(background_sprite);

	//Draw Game Objects
	//Player Draw
	player.draw(this->window);

	//Enemy draw
	for (unsigned i = 0; i < enemies.size(); i++) {
		enemies[i].draw(this->window);
	}

	//Particle draw
	particle_generator.draw(this->window);

	//Draw UI
	distance_traveled_text.setString(std::to_string((int)(distance_traveled / 100)) + "m");
	distance_traveled_text.setPosition(camera.x + 8, camera.y + 8);

	if (player.game_over) {
		game_over_text.setString("Game Over!\nDistance Traveled: " + std::to_string((int)(distance_traveled / 100)) + "m\n\n [PRESS SPACE]");
		game_over_text.setPosition(camera.x + 8, camera.y + 8);
		this->window->draw(game_over_text);
	}
	else {
		this->window->draw(distance_traveled_text);
	}

	this->window->display();
}