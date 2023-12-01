#pragma once

#include <iostream>

#include <vector>
#include <cmath>

#include <SFML/Graphics.hpp>

namespace HelperScripts {
	extern double PI;
	double DegToRad(float deg);
	float Lerp(float val, float tar, float t);
	float AngleBetween(float x0, float y0, float x1, float y1);
	float SnapToGrid(float value, float size);
	float RandomRange(float x0, float x1);
	sf::IntRect ChooseIntRect(std::vector<sf::IntRect> args);
	float Lengthdir_x(float _length, float _dir);
	float Lengthdir_y(float _length, float _dir);
};