#include <SFML/Graphics.hpp>
#include "game.h"
#include "bullet.h"
#include <iostream>

using namespace sf;
using namespace std;

sf::Texture spritesheet;
std::vector<Ship*> ships;

unsigned char* bulletPointer;
std::vector<Bullet*> bullets;

Player* player;


void Reset() {
	Invader::speed = 25.f;
}

void Load() {
	if (!spritesheet.loadFromFile("res/img/invaders_sheet.png")) {
		cerr << "Failed to load spritesheet!" << std::endl;
	}

	for (int r = 0; r < invaders_rows; r++) {
		for (int c = 0; c < invaders_columns; c++) {
			Invader* inv = new Invader(sf::IntRect(r * 32, 0, 32, 32), { c * 50.f + 50, r * 40.f + 50 });
			ships.push_back(inv);
		}
	}

	player = new Player();
	ships.push_back(player);
		
	Bullet::Init();
	Reset();
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