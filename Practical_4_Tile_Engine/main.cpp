//main.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "Player.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;

bool _finished = false;
auto player = make_unique<Player>();

void Load() {
	ls::loadLevelFile("res/maze_2.txt", 100.f);

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
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
	ls::Render(window);
	player->Render(window);
}

int main() {
	Load();
	RenderWindow window(VideoMode(ls::getWindowWidth(), ls::getWindowHeight()), "Tiles Engine");
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}