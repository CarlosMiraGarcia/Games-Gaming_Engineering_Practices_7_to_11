#pragma once
#include "LevelSystem.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

constexpr float_t _playerSize = 25.f;

constexpr Keyboard::Key controls[4] = {
	Keyboard::A, // Player1 Left
	Keyboard::D, // Player1 Right	
	Keyboard::W, // Player1 Up
	Keyboard::S, // Player1 Down
};
