#include "HelperScripts.h"

namespace HelperScripts {
	double PI = 3.14159265359;
}

double HelperScripts::DegToRad(float deg) {
	return (deg * PI) / 180;
};

float HelperScripts::Lerp(float val, float tar, float t) {
	return val + t * (tar - val);
}

float HelperScripts::AngleBetween(float x0, float y0, float x1, float y1) {

	return (float)((int)(atan((y1 - y0) / (x1 - x0)) * (180 / PI) + 360 ) % 360);
}

float HelperScripts::SnapToGrid(float value, float size)
{
	return std::floor(value / size) * size;
}

float HelperScripts::RandomRange(float x0, float x1) {
	float r = x0 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (x1 - x0)));
	return r;
}

sf::IntRect HelperScripts::ChooseIntRect(std::vector<sf::IntRect> args) {
	return args[rand() % args.size()];
}

float HelperScripts::Lengthdir_x(float _length, float _dir) {
	return _length * (float)cos(_dir * PI / -180);
}

float HelperScripts::Lengthdir_y(float _length, float _dir) {
	return _length * (float)sin(_dir * PI / -180);
}