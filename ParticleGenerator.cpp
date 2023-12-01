#include "ParticleGenerator.h"

Particle::Particle(float _x, float _y, ParticleType _type, float _life, float _angle) {
	x = _x;
	y = _y;
	life_max = _life;
	life = life_max;
	alpha = 1;
	type = _type;
	angle = _angle;

	texture = TextureManager::Acquire("Resources/Sprites/sParicleTextures.png");
	sprite.setTexture(*texture);

	switch (_type) {
		case blood_floor:
			sprite.setTextureRect(HelperScripts::ChooseIntRect(std::vector<sf::IntRect>{sf::IntRect(0,0,31,26), sf::IntRect(34, 0, 24, 20)}));
		break;

		case truck_tire:
			sprite.setTextureRect(sf::IntRect(60, 0, 5, 5));
		break;
	}

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

ParticleGenerator::ParticleGenerator() {
	
}

void ParticleGenerator::draw(sf::RenderWindow* window) {
	for (unsigned i = 0; i < particles.size(); i++) {
		particles[i].sprite.setPosition(particles[i].x,particles[i].y);
		particles[i].sprite.setColor(sf::Color(255,255,255,(sf::Uint8)particles[i].alpha));
		particles[i].sprite.setRotation(particles[i].angle);
		window->draw(particles[i].sprite);
	}
}

void ParticleGenerator::update() {
	for (unsigned i = 0; i < particles.size(); i++) {
		switch (particles[i].type) {
			case blood_floor:
				particles[i].alpha = 255 * (particles[i].life / particles[i].life_max);

			break;
			case truck_tire:
				particles[i].alpha = 255 * (particles[i].life / particles[i].life_max);

			break;
		}

		//Kill particles
		if (particles[i].life <= 0) {
			//Get vector index of this enemy
			int _indx = 0;
			for (unsigned i = 0; i < particles.size(); i++) {
				Particle* e = &particles.at(i);
				if (e == &particles[i]) {
					_indx = i;
				}
			}
			if (_indx != -1) {
				//Delete this particle
				particles.erase(particles.begin() + 0);
				return;
			}
		}
		else {
			particles[i].life--;
		}
	}
}

void ParticleGenerator::Emit(float _x, float _y, ParticleType _type, float _life, float _angle) {
	Particle p = Particle(_x, _y, _type, _life, _angle);
	particles.push_back(p);
}