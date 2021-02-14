#include <SFML/Graphics.hpp>
#include "game.h"
#include <iostream>
#include "Player.h"

using namespace sf;
using namespace std;

auto player = make_unique<Player>();

void Load() {

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

	// Keyboard binds
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
		
	player->Update(dt);
}
void Render(RenderWindow& window) {
	player->Render(window);
}

int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Tiles Engine");
	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}