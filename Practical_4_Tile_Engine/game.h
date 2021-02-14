#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;


constexpr Keyboard::Key controls[4] = {
	Keyboard::A, // Player1 Left
	Keyboard::D, // Player1 Right	
	Keyboard::W, // Player1 Up
	Keyboard::S, // Player1 Down
};
