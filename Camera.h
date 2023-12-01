#pragma once

#include "HelperScripts.h"
#include "Player.h"

#include <SFML/Graphics.hpp>

class Camera {
private:

public:
	Camera(float _x, float _y, int _w, int _h);
	virtual ~Camera();

	float x;
	float y;
	int w;
	int h;
	float fric;
	float win_w;
	float win_h;
	float shake_amnt;
	float zoom;
	Player* target_player{};

	sf::View view;

	void update(float dt);
};