#include "Camera.h"

Camera::Camera(float _x, float _y, int _w, int _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	fric = 0.1f;
	win_w = 1280;
	win_h = 960;
	zoom = 0;
	view.reset(sf::FloatRect((float)_x, (float)_y, (float)_w, (float)_h));
}

Camera::~Camera() {
	
}

void Camera::update(float dt) {
	shake_amnt = HelperScripts::Lerp(shake_amnt, 0, .1f);

	if (&target_player != nullptr) {
		x = HelperScripts::Lerp(x, target_player->x + (target_player->hsp * 50) - (w / 2) + HelperScripts::RandomRange(-shake_amnt, shake_amnt), .03f);
		y = HelperScripts::Lerp(y, target_player->y + (target_player->vsp * 50) - (h / 2) + HelperScripts::RandomRange(-shake_amnt, shake_amnt), .03f);
	}

	view.reset(sf::FloatRect((float)x, (float)y, (float)w, (float)h));
	view.zoom(1 - zoom);
}