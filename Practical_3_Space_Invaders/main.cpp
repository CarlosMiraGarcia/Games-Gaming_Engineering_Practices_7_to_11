#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include <iostream>

using namespace sf;
using namespace std;

std::vector<Ship*> ships;
Player* player = new Player();

sf::Texture spritesheet;

void Load() {

	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	for (int r = 0; r < invaders_columns; ++r) {
		auto rect = IntRect(0, 0, 32, 32);
		for (int c = 0; c < invaders_rows; ++c) {
			float x_pos = (r * 32) + 32;
			float y_pos = (c * 26) + 32;
			Vector2f position = Vector2f{ x_pos, y_pos};
			auto inv = new Invader(rect, position);
			ships.push_back(inv);
		}
	}

	ships.push_back(player);
}

void Update(RenderWindow& window) {

	// Reset clock, recalculate deltatime
	static Clock clockDelta;
	float dt = clockDelta.restart().asSeconds();

	// Check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}

	for (auto& s : ships) {
		s->Update(dt);
	}

	// Keyboard binds
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}	
}

void Render(RenderWindow& window) {

	for (const auto s : ships) {
		window.draw(*s);
	}
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Space Invaders");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}