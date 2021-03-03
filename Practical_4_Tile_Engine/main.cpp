#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "Player.h"
#include "LevelSystem.h"

using namespace sf;
using namespace std;
sf::Text timerText;
sf::Text bestTimer;
sf::Font font;

auto player = make_unique<Player>();
float timerValue;
float bestValue;
sf::Clock playerTimer;

void Load() {
	ls::setColor(ls::TILE::WALL, sf::Color::Blue);

	ls::loadLevelFile("res/maze_2.txt", 100.f);
	ls::setColor(ls::TILE::WALL, sf::Color::Blue);
	;	vector<Vector2ul> tile = ls::findTiles(LevelSystem::TILE::START);
	player->setPosition(Vector2f(ls::getTilePosition(tile[0]) + Vector2f(_playerSize, _playerSize)));

	// Print the level to the console
	for (size_t y = 0; y < ls::getHeight(); ++y) {
		for (size_t x = 0; x < ls::getWidth(); ++x) {
			cout << ls::getTile({ x, y });
		}
		cout << endl;
	}
	playerTimer.restart();

	//Load font-face from res direction
	font.loadFromFile("res/Fira.otf");
	// Set timerText properties
	timerText.setFont(font);
	timerText.setCharacterSize(28);
	timerText.setFillColor(sf::Color::Black);
	timerText.setString(to_string(timerValue));
	sf::FloatRect timerTextRect = timerText.getLocalBounds();
	timerText.setOrigin(timerTextRect.width / 2, timerTextRect.height / 2);
	timerText.setPosition(sf::Vector2f(ls::getWindowWidth() / 2, 10));
	// Set timerText properties
	bestTimer.setFont(font);
	bestTimer.setCharacterSize(28);
	bestTimer.setFillColor(sf::Color::Black);
	bestTimer.setString(to_string(bestValue));
	sf::FloatRect bestTextRect = timerText.getLocalBounds();
	bestTimer.setOrigin(bestTextRect.width / 2, bestTextRect.height / 2);
	bestTimer.setPosition(sf::Vector2f(200, 10));
}

void Update(RenderWindow& window) {
	sf::Time elapsed1 = playerTimer.getElapsedTime();
	timerValue = elapsed1.asSeconds();
	timerText.setString(to_string(timerValue));

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

	if (player->isFinished() == true) {
		playerTimer.restart();

		if (timerValue < bestValue || bestValue == 0) {
			bestValue = timerValue;
		}
		Load();
		player->_finished = false;
	}
}

void Render(RenderWindow& window) {
	ls::Render(window);
	player->Render(window);
	window.draw(timerText);
	window.draw(bestTimer);
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