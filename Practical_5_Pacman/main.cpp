#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Player.h"
#include "game.h"

using namespace sf;
using namespace std;

auto player = make_unique<Player>();

void Load() {
	ls::setColor(ls::TILE::WALL, sf::Color::Color(0x002121DEff));
	ls::loadLevelFile("res/pacman.txt", _tileSize);
	vector<Vector2ul> tile = ls::findTiles(ls::TILE::START);
	player->setPosition(Vector2f(ls::getTilePosition(tile[0]) + Vector2f(_playerSize, _playerSize)));

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
	RenderWindow window(VideoMode(ls::getWindowWidth(), ls::getWindowHeight()), "Pacman");
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}