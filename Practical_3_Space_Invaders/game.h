#pragma once
#include <SFML/Graphics.hpp>
#include "ship.h"
#include "bullet.h"

using namespace sf;
using namespace std;

constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;
constexpr uint16_t invaders_rows = 5;
constexpr uint16_t invaders_columns = 14;
constexpr Keyboard::Key controls[3] = {
	Keyboard::A, // Player1 Left
	Keyboard::D, // Player1 Right
	Keyboard::Space // Player1 Fire
};

extern sf::Texture spritesheet;
extern std::vector<Ship*> ships;
extern Player* player;


