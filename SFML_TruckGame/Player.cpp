#include "Player.h"

Player::Player(float _x, float _y) {
	x = _x;
	y = _y;
	spd = 5;
	start_fric = 0.03f;
	end_fric = 0.07f;
	hsp = 0;
	vsp = 0;
	angle = 45;

	//Load Texture
	//layers
	for (int i = 0; i < 20; i++) {
		texture[i] = TextureManager::Acquire("Resources/Sprites/sPlayerTruck.png");
		sprite[i].setTexture(*texture[i]);
		sprite[i].setTextureRect(sf::IntRect(46 * i, 0, 46,18));
		sprite[i].setOrigin(sprite[i].getLocalBounds().width / 2, sprite[i].getLocalBounds().height / 2);
	}

	//shadow
	shadow_texture = TextureManager::Acquire("Resources/Sprites/sPlayerTruckShadow.png");
	shadow_sprite.setTexture(*shadow_texture);
	shadow_sprite.setOrigin(shadow_sprite.getLocalBounds().width/2, shadow_sprite.getLocalBounds().height / 2);

	//mask
	mask_texture = TextureManager::Acquire("Resources/Sprites/sPlayerTruckMask.png");
	mask_sprite.setTexture(*mask_texture);
	mask_sprite.setOrigin(mask_sprite.getLocalBounds().width / 2, mask_sprite.getLocalBounds().height / 2);

	//Audio
	truck_sound_buffer = AudioManager::Acquire("Resources/Sounds/truck.wav");
	truck_sound.setBuffer(*truck_sound_buffer);

	//Start playing truck idle sound
	truck_sound.setLoop(true);
	truck_sound.setVolume(70);
	truck_sound.play();
}

void Player::update(float dt) {
	//Movement
	if (!game_over) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			hsp = HelperScripts::Lerp(hsp, (float)cos(HelperScripts::DegToRad(angle)) * spd, start_fric);
			vsp = HelperScripts::Lerp(vsp, (float)sin(HelperScripts::DegToRad(angle)) * spd, start_fric);
			started = true;
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
				hsp = HelperScripts::Lerp(hsp, (float)cos(HelperScripts::DegToRad(angle + 180)) * spd, start_fric);
				vsp = HelperScripts::Lerp(vsp, (float)sin(HelperScripts::DegToRad(angle + 180)) * spd, start_fric);
				started = true;
			}
			else {
				hsp = HelperScripts::Lerp(hsp, 0, end_fric);
				vsp = HelperScripts::Lerp(vsp, 0, end_fric);
			}
		}
}

	//Tire Particles
	if (tire_particle_t++ >= tire_particle_tmax) {
		if (abs(hsp) > 1 || abs(vsp) > 1) {
			particle_generator->Emit(x + HelperScripts::Lengthdir_x(16, angle + 135), y + HelperScripts::Lengthdir_y(16, angle + 135), truck_tire, 300, angle);
			particle_generator->Emit(x + HelperScripts::Lengthdir_x(16, angle + 225), y + HelperScripts::Lengthdir_y(16, angle + 225), truck_tire, 300, angle);
		}
		tire_particle_t = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		angle += 10 * (abs(hsp) + abs(vsp)) * 0.1f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		angle -= 10 * (abs(hsp) + abs(vsp)) * 0.1f;
	}

	x += hsp;
	y += vsp;

	shadow_sprite.setPosition(x,y);
	shadow_sprite.setRotation(angle);

	mask_sprite.setPosition(x, y);
	mask_sprite.setRotation(angle);

	for (int i = 0; i < 20; i++) {
		sprite[i].setPosition(x, y - i);
		sprite[i].setRotation(angle);
	}

	//Stop Time
	if (started) {
		if (abs(hsp) < 1 && abs(vsp) < 1 && started) {
			if (stop_t++ >= stop_tmax) {
				game_over = true;
			}
		}
		else {
			stop_t = HelperScripts::Lerp(stop_t, 0, .05f);
		}
	}

	//Truck idle sound pitch
	truck_sound.setPitch(1 + (std::sqrt((hsp * hsp) + (vsp * vsp)) * .15f));
}

void Player::draw(sf::RenderWindow *window) {
	window->draw(shadow_sprite);
	for (int i = 0; i < 20; i++) {
		window->draw(sprite[i]);
	}
}