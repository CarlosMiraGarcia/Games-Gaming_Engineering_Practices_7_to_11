#include <SFML/Graphics.hpp>
#include <iostream>
#include "LevelSystem.h"
#include "Player.h"
#include "Entity.h"
#include "Ghost.h"
#include "game.h"
#include "main.h"

using namespace sf;
using namespace std;

auto player = new Player();
std::vector<Entity*> characters;

void Load() {

	ls::setColor(ls::TILE::WALL, sf::Color::Color(0x002121DEff));
	ls::loadLevelFile("res/pacman.txt", _tileSize);
	vector<Vector2ul> tile = ls::findTiles(ls::TILE::START);
	player->setPosition(Vector2f(ls::getTilePosition(tile[0]) + Vector2f(_playerSize, _playerSize)));
	characters.push_back(player);

	for (int i = 0; i <= 0; i++) {
		auto ghost = new Ghost(ghostColours[i]);	
		vector<Vector2ul> tile = ls::findTiles(ls::TILE::ENEMY);
		ghost->setPosition(Vector2f(ls::getTilePosition(tile[i]) + Vector2f(_ghostSize, _ghostSize)));
		characters.push_back(ghost);
	}

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

	for (auto& c : characters) {
		c->Update(dt);
	}
}
void Render(RenderWindow& window) {
	ls::Render(window);
	for (const auto c : characters) {
		c->Render(window);
	}
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