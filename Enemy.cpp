#include "Enemy.h"

SoundManager gameSounds;

Enemy::Enemy(float _x, float _y, float _spd, float _dir)
			:
	run_animation("Resources/Sprites/sEnemyRun.png", 0, 0, 16, 16)
{
	x = _x;
	y = _y;
	spd = _spd;
	dir = _dir;

	//Load Sprites
	run_animation.ApplyToSprite(run_sprite);
	run_sprite.setOrigin(run_sprite.getLocalBounds().width / 2, run_sprite.getLocalBounds().height);
	//shadow
	shadow_texture = TextureManager::Acquire("Resources/Sprites/sEnemyShadow.png");
	shadow_sprite.setTexture(*shadow_texture);
	shadow_sprite.setOrigin(shadow_sprite.getLocalBounds().width / 2, shadow_sprite.getLocalBounds().height / 2);
}

Enemy::~Enemy() {

}

void Enemy::Kill() {
	//Get vector index of this enemy
	int _indx = -1;
	for (unsigned i = 0; i < enemies->size(); i++) {
		Enemy* e = &enemies->at(i);
		if (e == this) {
			_indx = i;
		}
	}
	if (_indx != -1) {
		//Delete this enemy
		enemies->erase(enemies->begin() + _indx);
		return;
	}
}

void Enemy::update(float dt) {
	hsp = (float)cos(HelperScripts::DegToRad(dir)) * spd;
	vsp = (float)sin(HelperScripts::DegToRad(dir)) * spd;

	x += hsp;
	y += vsp;

	//Play running animation
	run_animation.update(dt);
	run_animation.ApplyToSprite(run_sprite);
	if (hsp != 0) {
		run_sprite.setScale(signbit(hsp) ? 1.0f : -1.0f, 1.0f);
	}

	//Check Collision
	if (run_sprite.getGlobalBounds().intersects(player->mask_sprite.getGlobalBounds())) {
		//Check the truck is fast
		if (abs(player->hsp) > 1.5 || abs(player->vsp) > 1.5) {
			//Spawn blood particles
			camera->shake_amnt = 150;
			player->game_over = true;
			player->hsp = 0;
			player->vsp = 0;
			gameSounds.RunOver(50, 1 + HelperScripts::RandomRange(-.3f, .3f), false);
			particle_generator->Emit(x, y, blood_floor, 300, 0);
			Kill();
		}
		else
		{
			//Avoid truck if it is slow
			if (abs(hsp) > abs(vsp)) {
				while (y > player->sprite[0].getGlobalBounds().top) {
					y--;
				}
			}
			else {
				while (x > player->sprite[0].getGlobalBounds().left) {
					x--;
				}
			}
		}
	}

	//Kill after walking off screen
	//Top
	if (y < camera->y - 128 && vsp < .1) {
		Kill();
	}
	//Right
	if (x > camera->x + camera->w + 128 && hsp > .1) {
		Kill();
	}
	//Bottom
	if (y > camera->y + camera->h + 128 && vsp > .1) {
		Kill();
	}
	//Left
	if (x < camera->x - 128 && hsp < .1) {
		Kill();
	}
}

void Enemy::draw(sf::RenderWindow* window) {
	shadow_sprite.setPosition(x, y);
	window->draw(shadow_sprite);

	run_sprite.setPosition(x, y);
	window->draw(run_sprite);
}