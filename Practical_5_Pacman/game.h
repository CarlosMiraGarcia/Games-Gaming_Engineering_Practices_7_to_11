#pragma once
#include "LevelSystem.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

constexpr float_t _tileSize = 24.f;
constexpr float_t _playerSize = _tileSize/2;
constexpr float_t _ghostSize = _tileSize/2;
constexpr int32_t ghostColours[4] = { 0x00FF0000ff, 0x00FFB8FFff, 0x0000FFFFff, 0x00FFB852ff };

constexpr Keyboard::Key controls[4] = {
	Keyboard::A, // Player1 Left
	Keyboard::D, // Player1 Right	
	Keyboard::W, // Player1 Up
	Keyboard::S, // Player1 Down
};
